#include "stdafx.h"
using namespace shared;

static const std::string PCHACK_PROJECT_REG_PATH = \
R"(HKEY_LOCAL_MACHINE\SOFTWARE\SKSTU\PROJECTS\PCHACK\)";

bool Win::PCHack::HasInjectionModuleBeenRunning(const std::string& sysproimgname) {
	bool running = false;
	do {
		std::set<DWORD> target_process = Process::Get(sysproimgname + ".exe");
		if (target_process.empty())
			break;
		const DWORD dwProcessIdCurrent = *target_process.begin();
		const DWORD64 dwCreateTimeCurrent = shared::Win::Process::GetProcessCreateTime(dwProcessIdCurrent);

		DWORD dwProcessIdPrev = 0;
		DWORD64 dwCreateTimePrev = 0;
		std::string binPid, binCreateTime;
		if (!shared::Win::Registry::NtRead(PCHACK_PROJECT_REG_PATH + sysproimgname + R"(\PID)", binPid))
			break;
		if (!shared::Win::Registry::NtRead(PCHACK_PROJECT_REG_PATH + sysproimgname + R"(\CREATE_TIME)", binCreateTime))
			break;
		memcpy(&dwProcessIdPrev, binPid.data(), sizeof(DWORD));
		memcpy(&dwCreateTimePrev, binCreateTime.data(), sizeof(DWORD64));
		if (dwProcessIdCurrent != dwProcessIdPrev)
			break;
		if (dwCreateTimeCurrent != dwCreateTimePrev)
			break;
		running = true;
	} while (0);
	return running;
}
bool Win::PCHack::SetInjectionModuleRunningFlag(const bool&, const std::string& sysproimgname) {
	bool result = false;
	do {
		std::set<DWORD> target_process = Process::Get(sysproimgname + ".exe");
		if (target_process.empty())
			break;
		const DWORD dwProcessIdCurrent = *target_process.begin();
		const DWORD64 dwCreateTimeCurrent = shared::Win::Process::GetProcessCreateTime(dwProcessIdCurrent);

		std::string binPid, binCreateTime;
		binPid.append((char*)&dwProcessIdCurrent, sizeof(DWORD));
		binCreateTime.append((char*)&dwCreateTimeCurrent, sizeof(DWORD64));
		if (!shared::Win::Registry::NtWrite(PCHACK_PROJECT_REG_PATH + sysproimgname + R"(\PID)", binPid, REG_DWORD))
			break;
		if (!shared::Win::Registry::NtWrite(PCHACK_PROJECT_REG_PATH + sysproimgname + R"(\CREATE_TIME)", binCreateTime, REG_QWORD))
			break;
		result = true;
	} while (0);
	return result;
}