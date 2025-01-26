#include "stdafx.h"

namespace shared {
	bool Win::Process::GetProcessProtectionLevel(const DWORD& dwProcessId, DWORD& outLevel) {
		bool result = false;
		outLevel = 0;
		HANDLE hProcess = NULL;
		do {
			hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, dwProcessId);
			if (!hProcess)
				break;
			PROCESS_PROTECTION_LEVEL_INFORMATION level = { 0 };
			if (FALSE == GetProcessInformation(hProcess, ProcessProtectionLevelInfo, &level, sizeof(level)))
				break;
			outLevel = level.ProtectionLevel;
			result = true;
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}

#if 0
#define SECURITY_MANDATORY_LABEL_AUTHORITY          {0,0,0,0,0,16}
#define SECURITY_MANDATORY_UNTRUSTED_RID            (0x00000000L)
#define SECURITY_MANDATORY_LOW_RID                  (0x00001000L)
#define SECURITY_MANDATORY_MEDIUM_RID               (0x00002000L)
#define SECURITY_MANDATORY_MEDIUM_PLUS_RID          (SECURITY_MANDATORY_MEDIUM_RID + 0x100)
#define SECURITY_MANDATORY_HIGH_RID                 (0x00003000L)
#define SECURITY_MANDATORY_SYSTEM_RID               (0x00004000L)
#define SECURITY_MANDATORY_PROTECTED_PROCESS_RID    (0x00005000L)
#endif
	std::wstring Win::Process::GetProcessPathnameByHwndW(const HWND& hwnd) {
		std::wstring result;
		DWORD dwPid = 0;
		HANDLE hProcess = NULL;
		do {
			if (!hwnd)
				break;
			::GetWindowThreadProcessId(hwnd, &dwPid);
			if (dwPid <= 0)
				break;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
			if (!hProcess)
				break;
			if (!hProcess)
				break;
			result.resize(_MAX_PATH, 0x00);
			DWORD pathLen =
				::GetModuleFileNameExW(hProcess, NULL, &result[0], _MAX_PATH);
			result.resize(pathLen);
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	bool Win::Process::IsExited(const DWORD& input_pid) {
		bool result = false;
		HANDLE hProcess = nullptr;
		do {
			if (input_pid <= 0)
				break;
			hProcess = OpenProcess(SYNCHRONIZE, FALSE, input_pid);
			if (hProcess == nullptr) {
				result = true;
				break;
			}
			DWORD r = WaitForSingleObject(hProcess, 0);
			switch (r) {
			case WAIT_OBJECT_0: {
				result = true;
			}break;
			default: {
				result = false;
			}break;
			}
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;

	}
	DWORD Win::Process::GetParentProcessId(const DWORD& input_pid) {
		DWORD result = 0;
		DWORD target_pid = input_pid ? input_pid : GetCurrentProcessId();
		HANDLE hSnapshot = nullptr;
		do {
			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hSnapshot == INVALID_HANDLE_VALUE || !hSnapshot)
				break;
			PROCESSENTRY32W pe32 = { 0 };
			pe32.dwSize = sizeof(PROCESSENTRY32W);
			if (FALSE == Process32FirstW(hSnapshot, &pe32))
				break;
			do {
				if (pe32.th32ProcessID == target_pid) {
					result = pe32.th32ParentProcessID;
					break;
				}
			} while (TRUE == Process32NextW(hSnapshot, &pe32));

		} while (0);
		SK_CLOSE_HANDLE(hSnapshot);
		return result;
	}
	std::wstring Win::Process::GetProcessPathnameByPidW(const DWORD& pid) {
		std::wstring result;
		HANDLE hProcess = NULL;
		do {
			if (pid <= 0)
				break;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			if (!hProcess)
				break;
			if (!hProcess)
				break;
			result.resize(_MAX_PATH, 0x00);
			DWORD pathLen =
				::GetModuleFileNameExW(hProcess, NULL, &result[0], _MAX_PATH);
			result.resize(pathLen);
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	std::string Win::Process::GetProcessPathnameByHwndA(const HWND& hwnd) {
		std::string result;
		DWORD dwPid = 0;
		HANDLE hProcess = NULL;
		do {
			if (!hwnd)
				break;
			::GetWindowThreadProcessId(hwnd, &dwPid);
			if (dwPid <= 0)
				break;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
			if (!hProcess)
				break;
			if (!hProcess)
				break;
			result.resize(_MAX_PATH, 0x00);
			DWORD pathLen =
				::GetModuleFileNameExA(hProcess, NULL, &result[0], _MAX_PATH);
			result.resize(pathLen);
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	std::string Win::Process::GetProcessPathnameByPidA(const DWORD& pid) {
		std::string result;
		HANDLE hProcess = NULL;
		do {
			if (pid <= 0)
				break;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			if (!hProcess)
				break;
			if (!hProcess)
				break;
			result.resize(_MAX_PATH, 0x00);
			DWORD pathLen =
				::GetModuleFileNameExA(hProcess, NULL, &result[0], _MAX_PATH);
			result.resize(pathLen);
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	bool Win::Process::GetProcessIntegrityLevel(const DWORD& dwProcessId, DWORD& outIntegrityLevel) {
		bool result = false;
		HANDLE hProcess = NULL;
		HANDLE hProcessToken = NULL;
		PTOKEN_MANDATORY_LABEL pLabel = NULL;
		DWORD dwLength = 0;
		do {
			hProcess = ::OpenProcess(/*PROCESS_QUERY_INFORMATION*/PROCESS_QUERY_LIMITED_INFORMATION, FALSE, dwProcessId);
			if (!hProcess)
				break;
			if (FALSE == ::OpenProcessToken(hProcess, TOKEN_QUERY, &hProcessToken) || !hProcessToken)
				break;
			::GetTokenInformation(hProcessToken, TokenIntegrityLevel, pLabel, dwLength, &dwLength);
			if (::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
				break;
			pLabel = (PTOKEN_MANDATORY_LABEL)LocalAlloc(LPTR, dwLength);
			if (!pLabel)
				break;
			if (FALSE == ::GetTokenInformation(hProcessToken, TokenIntegrityLevel, pLabel, dwLength, &dwLength))
				break;
			outIntegrityLevel = *::GetSidSubAuthority(pLabel->Label.Sid, *GetSidSubAuthorityCount(pLabel->Label.Sid) - 1);
			result = true;
		} while (0);
		if (pLabel) {
			::LocalFree(pLabel);
			pLabel = nullptr;
		}
		SK_CLOSE_HANDLE(hProcessToken);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	bool Win::Process::GetProcessProtectionLevel(const DWORD& dwProcessId, std::wstring& outLevelString) {
		bool result = false;
		outLevelString.clear();
		do {
			DWORD level = 0;
			if (!GetProcessProtectionLevel(dwProcessId, level))
				break;
			switch (level)
			{
			case PROTECTION_LEVEL_WINTCB_LIGHT:
				outLevelString = L"PsProtectedSignerWinTcb-Light";
				break;
			case PROTECTION_LEVEL_WINDOWS:
				outLevelString = L"PsProtectedSignerWindows";
				break;
			case PROTECTION_LEVEL_WINDOWS_LIGHT:
				outLevelString = L"PsProtectedSignerWindows-Light";
				break;
			case PROTECTION_LEVEL_ANTIMALWARE_LIGHT:
				outLevelString = L"PsProtectedSignerAntimalware-Light";
				break;
			case PROTECTION_LEVEL_LSA_LIGHT:
				outLevelString = L"PsProtectedSignerLsa-Light";
				break;
			case PROTECTION_LEVEL_WINTCB:
				outLevelString = L"PsProtectedSignerWinTcb";
				break;
			case PROTECTION_LEVEL_CODEGEN_LIGHT:
				outLevelString = L"PsProtectedSignerCodegen-Light";
				break;
			case PROTECTION_LEVEL_AUTHENTICODE:
				outLevelString = L"PsProtectedSignerAuthenticode";
				break;
			case PROTECTION_LEVEL_PPL_APP:
				outLevelString = L"PsProtectedSignerPplApp";
				break;
			case PROTECTION_LEVEL_NONE:
				outLevelString = L"None";
				break;
			default:
				outLevelString = L"Unknown";
			}
			result = true;
		} while (0);
		return result;
	}
	bool Win::Process::HasSystemSvchostProcess(const std::string& imgName, const std::string& account) {
		bool result = false;
		do {
			if (imgName.empty() || account.empty())
				break;
			if (::_stricmp("svchost.exe", imgName.c_str()))
				break;
			if (!::StrStrIA(account.c_str(), "system"))
				break;
			result = true;
		} while (0);
		return result;
	}
	bool Win::Process::HasExplorerProcess(const std::string& imgName, const std::string& commandLine) {
		bool result = false;
		do {
			//c:\windows\explorer.exe /factory,{75dff2b7-6936-4c06-a8bb-676a7b00b24b} -embedding
			if (!::StrStrIA(imgName.c_str(), "explorer.exe"))
				break;
			if (::StrStrIA("factory", commandLine.c_str()))
				break;
			if (::StrStrIA(",", commandLine.c_str()))
				break;
			if (::StrStrIA("-embedding", commandLine.c_str()))
				break;
			result = true;
		} while (0);
		return result;
	}
	bool Win::Process::Terminate(const DWORD& ProcessId) {
		bool result = false;
		HANDLE hProcess = nullptr;
		do {
			if (ProcessId <= 4)
				break;
			hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
			if (!hProcess)
				break;
			if (::TerminateProcess(hProcess, 3762) != TRUE)
				break;
#if 0
			::WaitForSingleObject(hProcess, 5000);
			::GetExitCodeProcess
#endif
				result = true;
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	void Win::Process::TerminateOnDirectory(const std::wstring& dir) {
		if (dir.empty())
			return;
		const auto self = GetCurrentProcessId();
		std::wstring ready_root = IConv::ToLowerW(dir);
		for (auto it = ready_root.begin(); it != ready_root.end();) {
			if (*it == L'\\' || *it == '/')
				it = ready_root.erase(it);
			else
				++it;
		}
		EnumW([&](
			const HANDLE& handle,
			const HANDLE& handle_token,
			const DWORD& pid,
			const std::wstring& account,
			const std::wstring& domain,
			const std::wstring& image,
			const std::wstring& image_path,
			bool& __break) {
				do {
					if (image_path.empty() || image.empty() || pid <= 4)
						break;
					if (self == pid)
						break;
					std::wstring dir = PathnameToPathW(image_path);
					dir = IConv::ToLowerW(dir);
					for (auto it = dir.begin(); it != dir.end();) {
						if (*it == L'\\' || *it == '/')
							it = dir.erase(it);
						else
							++it;
					}
					if (dir.find(ready_root) == std::wstring::npos)
						break;

					Terminate(pid);
				} while (0);
			});
	}
	bool Win::Process::Terminate(const std::string& ImageName) {
		bool result = false;
		do {
			if (ImageName.empty())
				break;
			Process::Enum(
				[&](const HANDLE& hProcess,
					const HANDLE& hProcessToken,
					const DWORD& dwProcessId,
					const std::string& AccountName,
					const std::string& DomainName,
					const std::string& imageName,
					const std::string& imagePathname,
					bool& __break)
				{
					HANDLE hProcessOpen = nullptr;
					do {
						if (dwProcessId <= 4)
							break;
						if (::_stricmp(imageName.c_str(), ImageName.c_str()))
							break;
						hProcessOpen = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
						if (!hProcess)
							break;
						if (::TerminateProcess(hProcess, 3762) != TRUE)
							break;
					} while (0);
					SK_CLOSE_HANDLE(hProcessOpen);
				});

			result = true;
		} while (0);
		return result;
	}
	DWORD Win::Process::GetAssignAccountNameProcess(const std::string& accountName) {
		DWORD result = 0;
		do {
			if (accountName.empty())
				break;
			Process::Enum(
				[&](const HANDLE& hProcess,
					const HANDLE& hProcessToken,
					const DWORD& dwProcessId,
					const std::string& AccountName,
					const std::string& DomainName,
					const std::string& imageName,
					const std::string& imagePathname,
					bool& __break)
				{
					if (0 == AccountName.compare(accountName)) {
						result = dwProcessId;
						__break = true;
					}
				});
		} while (0);
		return result;
	}
	std::map<DWORD, std::string> Win::Process::GetAssignAccountNameProcesses(const std::string& accountName) {
		std::map<DWORD, std::string> result;
		do {
			if (accountName.empty())
				break;
			Process::Enum(
				[&](const HANDLE& hProcess,
					const HANDLE& hProcessToken,
					const DWORD& dwProcessId,
					const std::string& AccountName,
					const std::string& DomainName,
					const std::string& imageName,
					const std::string& imagePathname,
					bool& __break)
				{
					if (0 == AccountName.compare(accountName))
						result.emplace(dwProcessId, imageName);
				});
		} while (0);
		return result;
	}
	std::string Win::Process::GetAccountName(const DWORD& dwProcessId) {
		std::string result;
		HANDLE hProcess = nullptr;
		HANDLE hProcessToken = nullptr;
		char* tokenInfoBuffer = nullptr;
		do {
			if (dwProcessId <= 4)
				break;
			hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
			if (!hProcess)
				hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);
			if (!hProcess)
				hProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId);
			if (!hProcess)
				break;
			if (!::OpenProcessToken(hProcess, TOKEN_QUERY, &hProcessToken))
				break;
			DWORD returnLen = 0;
			::GetTokenInformation(hProcessToken, TOKEN_INFORMATION_CLASS::TokenUser, nullptr, 0, &returnLen);
			if (returnLen <= 0)
				break;
			DWORD dwInBufferSize = returnLen;
			tokenInfoBuffer = new char[dwInBufferSize];
			::memset(tokenInfoBuffer, 0x00, dwInBufferSize);
			if (!::GetTokenInformation(hProcessToken, TOKEN_INFORMATION_CLASS::TokenUser, tokenInfoBuffer, dwInBufferSize, &returnLen))
				break;
			PTOKEN_USER pTokenUser = reinterpret_cast<PTOKEN_USER>(tokenInfoBuffer);
			SID_NAME_USE sid_name_user;
			char AccountName[_MAX_PATH] = { 0 };
			DWORD nAccountName = _MAX_PATH;
			char DomainName[_MAX_PATH] = { 0 };
			DWORD nDomainName = _MAX_PATH;
			if (!::LookupAccountSidA(NULL, pTokenUser->User.Sid, AccountName, &nAccountName, DomainName, &nDomainName, &sid_name_user))
				break;
			result.append(AccountName, nAccountName);
		} while (0);
		SK_DELETE_PTR_BUFFER(tokenInfoBuffer);
		SK_CLOSE_HANDLE(hProcessToken);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	void Win::Process::Enum(
		const std::function<void(const HANDLE&, const HANDLE&, const DWORD&, const std::string&, const std::string&, const std::string&, const std::string&, bool& __break)>& enum_cb) {
		HANDLE snapshot = nullptr;
		do {
			PROCESSENTRY32 ProcessEntry32;
			ProcessEntry32.dwSize = sizeof(ProcessEntry32);
			snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (!snapshot)
				break;
			BOOL flag = Process32FirstW(snapshot, &ProcessEntry32);
			while (flag) {
				if (ProcessEntry32.szExeFile[0]) {
					HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry32.th32ProcessID);
					if (!hProcess)
						hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessEntry32.th32ProcessID);
					if (!hProcess)
						hProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, ProcessEntry32.th32ProcessID);
					HANDLE hProcessToken = nullptr;
					std::string imagePathname;
					wchar_t AccountName[_MAX_PATH] = { 0 };
					DWORD nAccountName = _MAX_PATH;
					wchar_t DomainName[_MAX_PATH] = { 0 };
					DWORD nDomainName = _MAX_PATH;
					std::string image = IConv::WStringToUTF8(ProcessEntry32.szExeFile);
					DWORD ProcessId = ProcessEntry32.th32ProcessID;
					if (hProcess) {
						DWORD dwPath = _MAX_PATH;
						std::wstring wstrPath;
						wstrPath.resize(_MAX_PATH);
						if (::QueryFullProcessImageNameW(hProcess, 0, &wstrPath[0], &dwPath)) {
							wstrPath.resize(dwPath);
							imagePathname = IConv::WStringToUTF8(wstrPath);
						}
						else {
							dwPath = ::GetProcessImageFileNameW(hProcess, &wstrPath[0], wstrPath.size());
							if (dwPath) {
								wstrPath.resize(dwPath);
								imagePathname = IConv::WStringToUTF8(wstrPath);
							}
						}

						char* tokenInfoBuffer = nullptr;
						do {
							if (!::OpenProcessToken(hProcess, TOKEN_QUERY, &hProcessToken))
								break;
							DWORD returnLen = 0;
							::GetTokenInformation(hProcessToken, TOKEN_INFORMATION_CLASS::TokenUser, nullptr, 0, &returnLen);
							if (returnLen <= 0)
								break;
							DWORD dwInBufferSize = returnLen;
							tokenInfoBuffer = new char[dwInBufferSize];
							::memset(tokenInfoBuffer, 0x00, dwInBufferSize);
							if (!::GetTokenInformation(hProcessToken, TOKEN_INFORMATION_CLASS::TokenUser, tokenInfoBuffer, dwInBufferSize, &returnLen))
								break;
							PTOKEN_USER pTokenUser = reinterpret_cast<PTOKEN_USER>(tokenInfoBuffer);
							SID_NAME_USE sid_name_user;
							if (!::LookupAccountSidW(NULL, pTokenUser->User.Sid, AccountName, &nAccountName, DomainName, &nDomainName, &sid_name_user))
								break;
						} while (0);
						SK_DELETE_PTR_BUFFER(tokenInfoBuffer);
					}
					bool _break = false;
					if (enum_cb) {
						std::string account_name_u8, domain_name_u8;
						if (nDomainName > 0) {
							domain_name_u8 = IConv::WStringToUTF8(std::wstring(DomainName, nDomainName));
						}
						if (nAccountName > 0) {
							account_name_u8 = IConv::WStringToUTF8(std::wstring(AccountName, nAccountName));
						}
						enum_cb
						(
							hProcess,
							hProcessToken,
							ProcessId,
							account_name_u8.c_str(),
							domain_name_u8.c_str(),
							image,
							imagePathname,
							_break
						);
					}

					SK_CLOSE_HANDLE(hProcessToken);
					SK_CLOSE_HANDLE(hProcess);
					if (_break)
						break;
				}
				flag = ::Process32Next(snapshot, &ProcessEntry32);
			}
		} while (0);
		SK_CLOSE_HANDLE(snapshot);
	}
	void Win::Process::EnumW(
		const std::function<void(const HANDLE&, const HANDLE&, const DWORD&, const std::wstring&, const std::wstring&, const std::wstring&, const std::wstring&, bool& __break)>& enum_cb) {
		HANDLE snapshot = nullptr;
		do {
			PROCESSENTRY32W ProcessEntry32;
			ProcessEntry32.dwSize = sizeof(ProcessEntry32);
			snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (!snapshot)
				break;
			BOOL flag = Process32FirstW(snapshot, &ProcessEntry32);
			while (flag) {
				if (ProcessEntry32.szExeFile[0]) {
					HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry32.th32ProcessID);
					if (!hProcess)
						hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessEntry32.th32ProcessID);
					if (!hProcess)
						hProcess = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ, FALSE, ProcessEntry32.th32ProcessID);
					HANDLE hProcessToken = nullptr;
					std::wstring imagePathname;
					wchar_t AccountName[_MAX_PATH] = { 0 };
					DWORD nAccountName = _MAX_PATH;
					wchar_t DomainName[_MAX_PATH] = { 0 };
					DWORD nDomainName = _MAX_PATH;
					std::wstring image = ProcessEntry32.szExeFile;
					DWORD ProcessId = ProcessEntry32.th32ProcessID;
					if (hProcess) {
						DWORD dwPath = _MAX_PATH;
						std::wstring wstrPath;
						wstrPath.resize(_MAX_PATH);
						if (::QueryFullProcessImageNameW(hProcess, 0, &wstrPath[0], &dwPath)) {
							wstrPath.resize(dwPath);
							imagePathname = wstrPath;
						}
						else {
							dwPath = ::GetProcessImageFileNameW(hProcess, &wstrPath[0], wstrPath.size());
							if (dwPath) {
								wstrPath.resize(dwPath);
								imagePathname = wstrPath;
							}
						}

						char* tokenInfoBuffer = nullptr;
						do {
							if (!::OpenProcessToken(hProcess, TOKEN_QUERY, &hProcessToken))
								break;
							DWORD returnLen = 0;
							::GetTokenInformation(hProcessToken, TOKEN_INFORMATION_CLASS::TokenUser, nullptr, 0, &returnLen);
							if (returnLen <= 0)
								break;
							DWORD dwInBufferSize = returnLen;
							tokenInfoBuffer = new char[dwInBufferSize];
							::memset(tokenInfoBuffer, 0x00, dwInBufferSize);
							if (!::GetTokenInformation(hProcessToken, TOKEN_INFORMATION_CLASS::TokenUser, tokenInfoBuffer, dwInBufferSize, &returnLen))
								break;
							PTOKEN_USER pTokenUser = reinterpret_cast<PTOKEN_USER>(tokenInfoBuffer);
							SID_NAME_USE sid_name_user;
							if (!::LookupAccountSidW(NULL, pTokenUser->User.Sid, AccountName, &nAccountName, DomainName, &nDomainName, &sid_name_user))
								break;
						} while (0);
						SK_DELETE_PTR_BUFFER(tokenInfoBuffer);
					}
					bool _break = false;
					if (enum_cb) {
						std::wstring account_name, domain_name;
						if (nDomainName > 0) {
							domain_name = std::wstring(DomainName, nDomainName);
						}
						if (nAccountName > 0) {
							account_name = std::wstring(AccountName, nAccountName);
						}
						enum_cb
						(
							hProcess,
							hProcessToken,
							ProcessId,
							account_name.c_str(),
							domain_name.c_str(),
							image,
							imagePathname,
							_break
						);
					}

					SK_CLOSE_HANDLE(hProcessToken);
					SK_CLOSE_HANDLE(hProcess);
					if (_break)
						break;
				}
				flag = ::Process32NextW(snapshot, &ProcessEntry32);
			}
		} while (0);
		SK_CLOSE_HANDLE(snapshot);
	}
	std::map<DWORD, std::string> Win::Process::Enum() {
		std::map<DWORD, std::string> result;
		HANDLE snapshot = nullptr;
		do {
			PROCESSENTRY32 ProcessEntry32;
			ProcessEntry32.dwSize = sizeof(ProcessEntry32);
			snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (!snapshot)
				break;
			BOOL flag = ::Process32First(snapshot, &ProcessEntry32);
			while (flag) {
				if (ProcessEntry32.szExeFile[0]) {
					result.emplace(ProcessEntry32.th32ProcessID, IConv::WStringToUTF8(ProcessEntry32.szExeFile));
				}
				flag = ::Process32Next(snapshot, &ProcessEntry32);
			}
		} while (0);
		SK_CLOSE_HANDLE(snapshot);
		return result;
	}
	bool Win::Process::GetWinlogonProcessId(DWORD& pid) {
		bool result = false;
		const DWORD cursid = GetActiveConsoleSessionId();
		std::set<DWORD> winlogon_processes = Process::Get("winlogon.exe");
		do {
			if (winlogon_processes.empty())
				break;
			for (auto it = winlogon_processes.begin(); it != winlogon_processes.end(); ++it) {
				DWORD psid = 0;
				if (!GetSessionIdFromProcessId(*it, psid))
					break;
				if (cursid == psid) {
					pid = *it;
					result = true;
					break;
				}
			}
		} while (0);
#if 0

		do {
			if (winlogon_processes.empty())
				break;

			const DWORD current_sid = Win::GetActiveConsoleSessionId();
			std::time_t perv = 0;
			std::time_t next = 0;
			for (auto it = explorer_processes.begin(); it != explorer_processes.end();) {
				DWORD sessionId = 0;



				if (current_sid != Win::GetSessionIdFromProcessId(*it)) {
					it = explorer_processes.erase(it);
				}
				else {
					next = GetProcessCreateTime(*it);
					if (perv == 0) {
						perv = next;
						result = *it;
					}
					else {
						if (next < perv) {
							result = *it;
							perv = next;
						}
					}
					++it;
				}
			}
		} while (0);
#endif
		return result;
	}
	std::time_t Win::Process::GetProcessCreateTime(const DWORD& pid) {
		std::time_t result = 0;
		HANDLE hProcess = nullptr;
		do {
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
			if (!hProcess)
				break;
			FILETIME ftCreate, ftExit, ftKernel, ftUser;
			if (FALSE == GetProcessTimes(hProcess, &ftCreate, &ftExit, &ftKernel, &ftUser))
				break;

			result = Time::FileTimeToStamp(ftCreate);
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	bool Win::Process::GetExplorerProcessId(DWORD& pid) {
		bool result = false;
#if 0
		std::set<DWORD> explorer_processes = Process::Get("explorer.exe");
		do {
			if (explorer_processes.empty())
				break;

			const DWORD current_sid = Win::GetActiveConsoleSessionId();
			std::time_t perv = 0;
			std::time_t next = 0;
			for (auto it = explorer_processes.begin(); it != explorer_processes.end();) {
				if (current_sid != Win::GetSessionIdFromProcessId(*it)) {
					it = explorer_processes.erase(it);
				}
				else {
					next = GetProcessCreateTime(*it);
					if (perv == 0) {
						perv = next;
						result = *it;
					}
					else {
						if (next < perv) {
							result = *it;
							perv = next;
						}
					}
					++it;
				}
			}
		} while (0);
#endif
		return result;
	}
	//!@ At least administrator rights are required 
	//!@ 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\LastUsedUsername'
	DWORD Win::Process::GetCurrentUserProcessId() {
		DWORD result = 0;
		do {
			std::set<DWORD> current_processes = Process::Get("explorer.exe");
			if (!current_processes.empty()) {
				result = *current_processes.begin();
				break;
			}
			std::string Username;
			if (!Win::Registry::Read(
				R"(HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon\LastUsedUsername)",
				Username))
				break;
			if (Username.empty())
				break;
			Process::Enum([&](
				const HANDLE& hProcess,
				const HANDLE& hProcessToken,
				const DWORD& dwProcessId,
				const std::string& AccountName,
				const std::string& DomainName,
				const std::string& imageName,
				const std::string& imagePathname,
				bool& __break
				) {
					if (!::_stricmp(Username.c_str(), AccountName.c_str())) {
						result = dwProcessId;
						__break = true;
					}
				});
		} while (0);
		return result;
	}
	DWORD shared::Win::Process::GetPidOfEarliestCreationTime(const std::string& processName) {
		DWORD result = 0;
		do {
			auto pids = Win::Process::Get(processName);
			if (pids.empty())
				break;
			time_t prev = 0;
			time_t next = 0;
			for (const auto& pid : pids) {
				next = GetProcessCreateTime(pid);
				if (prev <= 0) {
					result = pid;
					prev = next;
				}
				else if (prev > next) {
					prev = next;
					result = pid;
				}
				else {

				}
			}
		} while (0);
		return result;
	}
	std::set<DWORD> shared::Win::Process::Get(const std::string& processName) {
		std::set<DWORD> result;
		do {
			if (processName.empty())
				break;
			PROCESSENTRY32W processEntry32 = { 0 };
			processEntry32.dwSize = sizeof(PROCESSENTRY32W);
			DWORD dw_pid = 0;
			HANDLE snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (snapshot == NULL)
				break;
			BOOL flag = ::Process32FirstW(snapshot, &processEntry32);
			while (flag) {
				if (processEntry32.szExeFile[0]) {
					if (!::_stricmp(IConv::WStringToMBytes(processEntry32.szExeFile).c_str(), processName.c_str()))
						result.emplace(processEntry32.th32ProcessID);
				}
				flag = ::Process32NextW(snapshot, &processEntry32);
			}
			SK_CLOSE_HANDLE(snapshot);
		} while (0);
		return result;
	}
	bool Win::Process::GetTimes(const HANDLE& hProcess, \
		std::uint64_t* creation_time /*= nullptr*/, std::uint64_t* kernel_time /*= nullptr*/, std::uint64_t* exit_time /*= nullptr*/, std::uint64_t* user_time /*= nullptr*/) {
		bool result = false;
		do {
			if (!hProcess)
				break;
			FILETIME CreationTime = { 0 };
			FILETIME ExitTime = { 0 };
			FILETIME KernelTime = { 0 };
			FILETIME UserTime = { 0 };
			if (FALSE == ::GetProcessTimes(hProcess, &CreationTime, &ExitTime, &KernelTime, &UserTime))
				break;
			if (creation_time)
				*creation_time = ((std::uint64_t)CreationTime.dwHighDateTime << 32)
				+ (std::uint32_t)CreationTime.dwLowDateTime;
			if (kernel_time)
				*kernel_time = ((std::uint64_t)KernelTime.dwHighDateTime << 32)
				+ (std::uint32_t)KernelTime.dwLowDateTime;
			if (exit_time)
				*exit_time = ((std::uint64_t)ExitTime.dwHighDateTime << 32)
				+ (std::uint32_t)ExitTime.dwLowDateTime;
			if (user_time)
				*user_time = ((std::uint64_t)UserTime.dwHighDateTime << 32)
				+ (std::uint32_t)UserTime.dwLowDateTime;
			result = true;
		} while (0);
		return result;
	}
	bool Win::Process::GetTimes(const DWORD& ProcessId,
		std::uint64_t* creation_time /*= nullptr*/, std::uint64_t* kernel_time /*= nullptr*/, std::uint64_t* exit_time /*= nullptr*/, std::uint64_t* user_time /*= nullptr*/) {
		bool result = false;
		HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
		do {
			if (!hProcess)
				break;
			if (!GetTimes(hProcess, creation_time, kernel_time, exit_time, user_time))
				break;
			result = true;
		} while (0);
		SK_CLOSE_HANDLE(hProcess);
		return result;
	}
	bool Win::Process::CreateA(
		const std::string& exePathname,
		const std::string& commandline,
		const std::function<void(const HANDLE& hProcess, const HANDLE& hThread, const DWORD& dwProcessId, const DWORD& dwThreadId)> create_process_cb,
		const DWORD& dwCreateFlags /*= CREATE_NEW_CONSOLE*/,
		const bool& Inheriting_parent_process /*= false*/,
		const bool& isShow /*= false*/,
		const DWORD& wait_time /*= 0*/) {
		bool result = false;
		do {
			STARTUPINFOA si = { 0 };
			si.cb = sizeof(si);
			if (!isShow) {
				si.dwXSize = 1;
				si.dwYSize = 1;
				si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESIZE;
			}
			else
				si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = isShow ? SW_SHOW : SW_HIDE;
			PROCESS_INFORMATION pi = { 0 };
			if (FALSE == ::CreateProcessA(
				exePathname.empty() ? NULL : exePathname.c_str(),   // No module name (use command line)
				commandline.empty() ? NULL : const_cast<char*>(("/c " + commandline).c_str()),        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				Inheriting_parent_process ? TRUE : FALSE,          // Set handle inheritance to FALSE
				dwCreateFlags,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				) {
				auto view_error = ::GetLastError();
				break;
			}
			::WaitForSingleObject(pi.hProcess, wait_time);
			if (create_process_cb)
				create_process_cb(pi.hProcess, pi.hThread, pi.dwProcessId, pi.dwThreadId);
			result = pi.hProcess != nullptr;
			SK_CLOSE_HANDLE(pi.hThread);
			//SK_CLOSE_HANDLE(pi.hProcess);
		} while (0);
		return result;
	}
	bool Win::Process::CreateA(
		const std::string& exePathname,
		const std::string& commandline,
		const std::function<void(const HANDLE&, const DWORD&)> create_process_cb,
		const bool& Inheriting_parent_process /*= false*/,
		const bool& isShow /*= false*/,
		const DWORD& wait_time /*= 0*/) {
		bool result = false;
		do {
			STARTUPINFOA si = { 0 };
			si.cb = sizeof(si);
			if (!isShow) {
				si.dwXSize = 1;
				si.dwYSize = 1;
				si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESIZE;
			}
			else
				si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = isShow ? SW_SHOW : SW_HIDE;
			PROCESS_INFORMATION pi = { 0 };
			if (FALSE == ::CreateProcessA(
				exePathname.empty() ? NULL : exePathname.c_str(),   // No module name (use command line)
				commandline.empty() ? NULL : const_cast<char*>(("/c " + commandline).c_str()),        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				Inheriting_parent_process ? TRUE : FALSE,          // Set handle inheritance to FALSE
				!Inheriting_parent_process ? CREATE_NEW_CONSOLE : NULL,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				) {
				auto view_error = ::GetLastError();
				break;
			}
			::WaitForSingleObject(pi.hProcess, wait_time);
			if (create_process_cb)
				create_process_cb(pi.hProcess, pi.dwProcessId);
			result = pi.hProcess != nullptr;
			SK_CLOSE_HANDLE(pi.hThread);
			//SK_CLOSE_HANDLE(pi.hProcess);
		} while (0);
		return result;
	}

	bool Win::Process::CreateWithTokenW(
		const std::string& exePathname,
		const std::string& commandline,
		const HANDLE& hToken,
		const std::function<void(const HANDLE&, const DWORD&)>& create_cb,
		const DWORD& dwCreateFlags /*= CREATE_NEW_CONSOLE*/,
		const bool& show /*= false*/,
		const DWORD& wait_time /*= 0*/) {
		bool result = false;
		wchar_t* pwCmd = nullptr;
		do {
			if (!hToken)
				break;
			if (!Win::AccessA(exePathname))
				break;

			AdjustProcessOrThreadPrivilege(::GetCurrentProcess(), SE_INCREASE_QUOTA_NAME, true);
			AdjustProcessOrThreadPrivilege(::GetCurrentProcess(), SE_ASSIGNPRIMARYTOKEN_NAME, true);

			if (!commandline.empty()) {
				std::wstring wCmd = IConv::MBytesToWString(commandline);
				pwCmd = new wchar_t[wCmd.size()];
				::wmemcmp(pwCmd, wCmd.data(), wCmd.size());
			}
			STARTUPINFOW si = { 0 };
			si.cb = sizeof(si);
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = show ? SW_SHOW : SW_HIDE;
			PROCESS_INFORMATION pi = { 0 };
			if (!::CreateProcessWithTokenW(hToken,
				LOGON_WITH_PROFILE,
				IConv::MBytesToWString(exePathname).c_str(), pwCmd, dwCreateFlags, NULL, NULL, &si, &pi))
				break;
			::WaitForSingleObject(pi.hProcess, wait_time);
			if (create_cb)
				create_cb(pi.hProcess, pi.dwProcessId);
			SK_CLOSE_HANDLE(pi.hThread);
			SK_CLOSE_HANDLE(pi.hProcess);
			result = true;
		} while (0);

		SK_DELETE_PTR_BUFFER(pwCmd);
		return result;
	}
	bool Win::Process::CreateAsUserA(
		const std::string& exePathname,
		const std::string& commandline,
		const HANDLE& hToken,
		const std::function<void(const HANDLE&, const DWORD&)>& create_cb,
		const bool& bInheritHandles /*= false*/,
		const DWORD& dwCreateFlags /*= CREATE_NEW_CONSOLE*/,
		const bool& show /*= false*/,
		const DWORD& wait_time /*= 0*/) {
		bool result = false;
		HANDLE hCreateProcessToken = nullptr;
		do {
			if (!hToken)
				break;
			if (!Win::AccessA(exePathname))
				break;
			//!@ 可能不需要调整 相应权限
			//AdjustProcessOrThreadPrivilege(::GetCurrentProcess(), SE_INCREASE_QUOTA_NAME, true);
			//AdjustProcessOrThreadPrivilege(::GetCurrentProcess(), SE_ASSIGNPRIMARYTOKEN_NAME, true);
			if (FALSE == ::DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityAnonymous, TokenPrimary, &hCreateProcessToken))
				break;
			STARTUPINFOA si = { 0 };
			si.cb = sizeof(si);
			PROCESS_INFORMATION pi = { 0 };
			if (!::CreateProcessAsUserA(
				hCreateProcessToken,
				exePathname.c_str(),
				const_cast<char*>(commandline.c_str()),
				NULL,
				NULL,
				bInheritHandles ? TRUE : FALSE,
				dwCreateFlags/*CREATE_PROTECTED_PROCESS*/,
				NULL,
				NULL,
				&si,
				&pi)) {
				auto error_no = ::GetLastError();
				break;
			}
			::WaitForSingleObject(pi.hProcess, wait_time);
			if (create_cb)
				create_cb(pi.hProcess, pi.dwProcessId);
			SK_CLOSE_HANDLE(pi.hThread);
			SK_CLOSE_HANDLE(pi.hProcess);
			result = true;
		} while (0);
		SK_CLOSE_HANDLE(hCreateProcessToken);
		return result;
	}
	bool Win::Process::CreateAsUserW(
		const std::wstring& exePathname,
		const std::wstring& commandline,
		const HANDLE& hToken,
		const std::function<void(const HANDLE&, const DWORD&)>& create_cb,
		const bool& bInheritHandles /*= false*/,
		const DWORD& dwCreateFlags /*= CREATE_NEW_CONSOLE*/,
		const bool& show /*= false*/,
		const DWORD& wait_time /*= 0*/) {
		bool result = false;
		HANDLE hCreateProcessToken = nullptr;
		do {
			if (!hToken)
				break;
			if (!Win::AccessW(exePathname))
				break;
			//!@ 可能不需要调整 相应权限
			//AdjustProcessOrThreadPrivilege(::GetCurrentProcess(), SE_INCREASE_QUOTA_NAME, true);
			//AdjustProcessOrThreadPrivilege(::GetCurrentProcess(), SE_ASSIGNPRIMARYTOKEN_NAME, true);
			if (FALSE == ::DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityAnonymous, TokenPrimary, &hCreateProcessToken))
				break;
			STARTUPINFOW si = { 0 };
			si.cb = sizeof(si);
			PROCESS_INFORMATION pi = { 0 };
			if (!::CreateProcessAsUserW(
				hCreateProcessToken,
				exePathname.c_str(),
				const_cast<wchar_t*>(commandline.c_str()),
				NULL,
				NULL,
				bInheritHandles ? TRUE : FALSE,
				dwCreateFlags/*CREATE_PROTECTED_PROCESS*/,
				NULL,
				NULL,
				&si,
				&pi)) {
				auto error_no = ::GetLastError();
				break;
			}
			::WaitForSingleObject(pi.hProcess, wait_time);
			if (create_cb)
				create_cb(pi.hProcess, pi.dwProcessId);
			SK_CLOSE_HANDLE(pi.hThread);
			SK_CLOSE_HANDLE(pi.hProcess);
			result = true;
		} while (0);
		SK_CLOSE_HANDLE(hCreateProcessToken);
		return result;
	}
	bool Win::Process::CreateAsParentA(
		const std::string& exePathname,
		const std::string& commandline,
		const HANDLE& hParent,
		const std::function<void(const HANDLE&, const DWORD&)>& create_cb,
		const bool& show /*= false*/, const DWORD& wait_time /*= 0*/) {
		bool result = false;
		LPPROC_THREAD_ATTRIBUTE_LIST AttributeList = nullptr;
		char* pCmd = nullptr;
		do {
			if (!Win::AccessA(exePathname))
				break;
			if (!hParent)
				break;
			SIZE_T lpsize = 0;
			::InitializeProcThreadAttributeList(NULL, 1, 0, &lpsize);
			if (lpsize <= 0)
				break;
			AttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST)new char[lpsize];
			if (FALSE == ::InitializeProcThreadAttributeList(AttributeList, 1, 0, &lpsize))
				break;
			if (FALSE == ::UpdateProcThreadAttribute(
				AttributeList,
				0,
				PROC_THREAD_ATTRIBUTE_PARENT_PROCESS,
				(void*)&hParent, sizeof(hParent),
				nullptr, nullptr))
				break;

			if (!commandline.empty()) {
				pCmd = new char[commandline.size()];
				::memcpy(pCmd, commandline.data(), commandline.size());
			}

			STARTUPINFOEXA siex = { 0 };
			siex.lpAttributeList = AttributeList;
			siex.StartupInfo.cb = sizeof(siex);
			siex.StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
			siex.StartupInfo.wShowWindow = show ? SW_SHOW : SW_HIDE;
			PROCESS_INFORMATION pi = { 0 };
			if (FALSE == ::CreateProcessA(exePathname.c_str(), pCmd, nullptr, nullptr, TRUE,
				CREATE_NEW_CONSOLE | EXTENDED_STARTUPINFO_PRESENT,
				nullptr, nullptr, &siex.StartupInfo, &pi))
				break;
			if (create_cb)
				create_cb(pi.hProcess, pi.dwProcessId);

			::WaitForSingleObject(pi.hProcess, wait_time);
			SK_CLOSE_HANDLE(pi.hProcess);
			SK_CLOSE_HANDLE(pi.hThread);
			result = true;
		} while (0);
		if (AttributeList) {
			delete[](char*)AttributeList;
			AttributeList = nullptr;
		}
		SK_DELETE_PTR_BUFFER(pCmd);
		return result;
	}
	bool shared::Win::Process::CreateA(
		const std::string& exePathname,
		const std::string& startParamenters,
		DWORD& outPID,
		const bool& Inheriting_parent_process /* = false*/,
		const bool& isShow /*= false*/,
		const DWORD& wait_time /*= 10000*/)
	{
		bool result = false;
		do {
			STARTUPINFOA si = { 0 };
			si.cb = sizeof(si);
			if (!isShow) {
				si.dwXSize = 1;
				si.dwYSize = 1;
				si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESIZE;
			}
			else
				si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = isShow ? SW_SHOW : SW_HIDE;
			PROCESS_INFORMATION pi = { 0 };
			if (0 == ::CreateProcessA(
				exePathname.empty() ? NULL : exePathname.c_str(),   // No module name (use command line)
				startParamenters.empty() ? NULL : const_cast<char*>(("/c " + startParamenters).c_str()),        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				Inheriting_parent_process ? TRUE : FALSE,          // Set handle inheritance to FALSE
				!Inheriting_parent_process ? CREATE_NEW_CONSOLE : NULL,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				)
				break;
			result = (outPID = pi.dwProcessId) != 0;
			::WaitForSingleObject(pi.hProcess, result ? wait_time : 0);
			SK_CLOSE_HANDLE(pi.hThread);
			SK_CLOSE_HANDLE(pi.hProcess);
		} while (0);
		return result;
	}

	bool Win::Process::CreateW(
		const std::wstring& exePathname,
		const std::wstring& startParamenters,
		DWORD& outPID,
		const bool& Inheriting_parent_process /* = false*/,
		const bool& isShow /*= false*/,
		const DWORD& wait_time /*= 10000*/)
	{
		bool result = false;
		do {
			STARTUPINFOW si = { 0 };
			si.cb = sizeof(si);
			if (!isShow) {
				si.dwXSize = 1;
				si.dwYSize = 1;
				si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESIZE;
			}
			else
				si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = isShow ? SW_SHOW : SW_HIDE;
			PROCESS_INFORMATION pi = { 0 };
			if (0 == ::CreateProcessW(
				exePathname.empty() ? NULL : exePathname.c_str(),   // No module name (use command line)
				startParamenters.empty() ? NULL : const_cast<wchar_t*>((L"/c " + startParamenters).c_str()),        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				Inheriting_parent_process ? TRUE : FALSE,          // Set handle inheritance to FALSE
				!Inheriting_parent_process ? CREATE_NEW_CONSOLE : NULL,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				)
				break;
			result = (outPID = pi.dwProcessId) != 0;
			::WaitForSingleObject(pi.hProcess, result ? wait_time : 0);
			SK_CLOSE_HANDLE(pi.hThread);
			SK_CLOSE_HANDLE(pi.hProcess);
		} while (0);
		return result;
	}


}///namespace shared 