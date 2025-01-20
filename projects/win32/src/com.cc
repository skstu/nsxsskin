#include "stdafx.h"
using namespace shared;

bool Win::Com::ToggleDesktop() {
	std::atomic_bool result = false;
	std::thread([&result]() {
		IShellDispatch4* pdisp = nullptr;
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		do {
			if (S_OK != hr)
				break;
			if (S_OK != ::CoCreateInstance(CLSID_Shell, NULL, CLSCTX_ALL,
				__uuidof(IShellDispatch4),
				(void**)&pdisp) ||
				!pdisp)
				break;
			if (S_OK != pdisp->ToggleDesktop())
				break;
			result.store(true);
		} while (0);
		SK_RELEASE_PTR(pdisp);
		CoUninitialize();
		}).join();
		return result.load();
}

bool Win::Com::ListenProcessOpen() {
	bool result = false;
#if 0
	int main() {
		HRESULT hres;

		// 初始化 COM
		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres)) {
			std::cout << "Failed to initialize COM library. Error code = 0x"
				<< std::hex << hres << std::endl;
			return 1; // Program has failed.
		}

		// 初始化安全
		hres = CoInitializeSecurity(
			NULL,
			-1,                          // COM negotiates service
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
		);

		if (FAILED(hres)) {
			std::cout << "Failed to initialize security. Error code = 0x"
				<< std::hex << hres << std::endl;
			CoUninitialize();
			return 1; // Program has failed.
		}

		// 获取 WMI 句柄
		IWbemLocator* pLoc = NULL;

		hres = CoCreateInstance(
			CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator, (LPVOID*)&pLoc);

		if (FAILED(hres)) {
			std::cout << "Failed to create IWbemLocator object. "
				<< "Err code = 0x" << std::hex << hres << std::endl;
			CoUninitialize();
			return 1; // Program has failed.
		}

		IWbemServices* pSvc = NULL;

		// Connect to the root\cimv2 namespace with the current user.
		hres = pLoc->ConnectServer(
			_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
			NULL,                    // User name. NULL = current user
			NULL,                    // User password. NULL = current
			0,                       // Locale. NULL indicates current
			NULL,                    // Security flags.
			0,                       // Authority (e.g. Kerberos)
			0,                       // Context object 
			&pSvc                    // pointer to IWbemServices proxy
		);

		if (FAILED(hres)) {
			std::cout << "Could not connect. Error code = 0x" << std::hex << hres << std::endl;
			pLoc->Release();
			CoUninitialize();
			return 1; // Program has failed.
		}

		// 设置 WMI 安全级别
		hres = CoSetProxyBlanket(
			pSvc,                        // Indicates the proxy to set
			RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
			RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
			NULL,                        // Server principal name 
			RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
			RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
			NULL,                        // client identity
			EOAC_NONE                    // proxy capabilities 
		);

		if (FAILED(hres)) {
			std::cout << "Could not set proxy blanket. Error code = 0x" << std::hex << hres << std::endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1; // Program has failed.
		}

		// 执行 WMI 查询
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM __InstanceCreationEvent WITHIN 1 WHERE TargetInstance ISA 'Win32_Process'"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (FAILED(hres)) {
			std::cout << "Query for processes failed. "
				<< "Error code = 0x" << std::hex << hres << std::endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1; // Program has failed.
		}

		IWbemClassObject* pclsObj = NULL;
		ULONG uReturn = 0;

		while (pEnumerator) {
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

			if (0 == uReturn) {
				break;
			}

			VARIANT vtProp;
			hr = pclsObj->Get(L"TargetInstance", 0, &vtProp, 0, 0);
			if (SUCCEEDED(hr)) {
				IWbemClassObject* pInstance = (IWbemClassObject*)vtProp.pdispVal;
				VARIANT vtName;
				hr = pInstance->Get(L"Name", 0, &vtName, 0, 0);
				if (SUCCEEDED(hr)) {
					std::wcout << "Process Name : " << vtName.bstrVal << std::endl;
					VariantClear(&vtName);
				}
				VariantClear(&vtProp);
				pInstance->Release();
			}

			pclsObj->Release();
		}

		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();

		return 0;
	}
#endif
	return result;
}