#include "stdafx.h"

double getRandomDouble() {
	// rand() 返回一个在 [0, RAND_MAX] 之间的整数
	double random_value = rand() / static_cast<double>(RAND_MAX); // 生成一个在 [0, 1] 之间的浮动值
	// 将其缩放到 [0.01, 0.1] 之间
	return 0.01 + (random_value * (0.1 - 0.01));
}

bool GetIPLocal(std::string& local_ipaddr) {
	bool result = false;
	local_ipaddr = "0.0.0.0";
	do {
		char* ret;
		char host_name[256] = "";
		WSADATA wsaData;
		WSAStartup(0x101, &wsaData);
		if (gethostname(host_name, 256))
			break;
		ret = inet_ntoa(*((struct in_addr*)gethostbyname(host_name)->h_addr));
		if (!ret)
			break;
		local_ipaddr = ret;
		result = true;
		//WSACleanup();
	} while (0);
	return result;
}

static httplib::Error ready(int& http_status_code, std::string& reason);

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nShowCmd
) {
#if defined(_DEBUG)
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//::_CrtSetBreakAlloc(106);
#endif
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	shared::Win::EnableDebugPrivilege();
	HANDLE hMutex = CreateMutexW(NULL, FALSE, L"XSInstallerProjectsProcessMutex");
	if (ERROR_ALREADY_EXISTS == GetLastError()) {
		return 3762;
	}
	
	Config::Get();

	SetProcessDPIAware();

	int status = 0;
	std::string reason;
	httplib::Error err = ready(status, reason);
	if (status != httplib::StatusCode::OK_200 || err != httplib::Error::Success) {
		std::string msg = fmt::format(R"(error: {}
status: {}
message: {}
reason: {}
)",
static_cast<int>(err),
status,
httplib::to_string(err),
reason.empty() ? "安装失败，无法安装" : reason
);

		MessageBoxW(NULL, stl::Conv::U8StringToWString(msg).c_str(), L"Installer", MB_TOPMOST | MB_ICONSTOP);
		return -1;
	}

	WindowThread windowThread;
	windowThread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);
	Config::Destroy();
	return 0;
}

httplib::Error ready(int& http_code, std::string& reason) {
	httplib::Error result = httplib::Error::Unknown;
	do {
		std::string config_url = INSTALLER_INTERFACE_CONFIG_URL_U8;
		std::wstring wstrstem = shared::Win::GetModuleNameW();
		do {
			auto f = wstrstem.find(L'.');
			if (f != std::wstring::npos) {
				wstrstem[f] = 0;
			}
			wstrstem = wstrstem.c_str();
			if (std::wstring::npos == wstrstem.find(L"_d") &&
				std::wstring::npos == wstrstem.find(L"-d") &&
				std::wstring::npos == wstrstem.find(L"-D") &&
				std::wstring::npos == wstrstem.find(L"_D"))
				break;
			config_url = INSTALLER_INTERFACE_CONFIG_URL_RELEASE_TEST;
		} while (0);
#if _DEBUG
		config_url = INSTALLER_INTERFACE_CONFIG_URL_RELEASE_TEST;
#endif
		config_url = INSTALLER_INTERFACE_CONFIG_URL_U8;
		httpparser::HttpUrlFields urlfield;
		if (!httpparser::Method::parse_http_url(config_url, urlfield))
			break;
		std::string url_host = urlfield[httpparser::EnHttpUrlFieldType::UF_HOST];
		std::string url_path = urlfield[httpparser::EnHttpUrlFieldType::UF_PATH];
		int url_port = atoi(urlfield[httpparser::EnHttpUrlFieldType::UF_PORT].c_str());
		if (!url_port)
			url_port = 80;
		httplib::Client cli(url_host, url_port);
		cli.set_connection_timeout(std::chrono::seconds(5));
		auto res = cli.Get(url_path);
		if (!res) {
			result = res.error();
			//MessageBoxA(NULL, httplib::to_string(err).c_str(), NULL, MB_TOPMOST);
			break;
		}
		http_code = res->status;
		if (http_code != httplib::StatusCode::OK_200)
			break;

		//MessageBoxA(NULL, res->body.c_str(), NULL, MB_TOPMOST);
		if (!(*Config::Get() << res->body)) {
			reason = R"(Invalid remote configure(1).)";
			break;
		}

		if (Config::Get()->GetInstaller().items_.empty()) {
			reason = R"(Invalid remote configure(2).)";
			break;
		}

		result = httplib::Error::Success;
	} while (0);
	return result;
}