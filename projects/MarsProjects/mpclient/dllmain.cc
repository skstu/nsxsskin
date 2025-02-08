#include "stdafx.h"

extern "C" {
	SHARED_API void MpClientUtilExportFunctions(void) {
		do {
			HANDLE hMutex = CreateMutexW(NULL, FALSE, L"XSLaunchStartupBootServiceMutex");
			if (ERROR_ALREADY_EXISTS == GetLastError())
				break;
			Launch::Get()->Start();
		} while (0);

		std::exit(3762);
	}

#pragma region{mpclient need}
	SHARED_API void MpConfigInitialize(void) {}
	SHARED_API void MpConfigUninitialize(void) {}
	SHARED_API void MpFreeMemory(void) {}
	SHARED_API void MpConfigRegisterForNotifications(void) {}
	SHARED_API void MpConfigGetValue(void) {}
	SHARED_API void MpConfigOpen(void) {}
	SHARED_API void MpConfigUnregisterNotifications(void) {}
	SHARED_API void MpConfigClose(void) {}
	SHARED_API void MpConfigGetValueAlloc(void) {}
	SHARED_API void MpConfigSetValue(void) {}
	SHARED_API void MpAllocMemory(void) {}
#pragma endregion{mpclient need}

}//extern "C"


//BOOL APIENTRY DllMain(_In_ void* _DllHandle, _In_ unsigned long _Reason, _In_opt_ void* _Reserved) {
//	switch (_Reason) {
//	case DLL_PROCESS_ATTACH: {
//
//	}break;
//	case DLL_THREAD_ATTACH: {
//	}break;
//	case DLL_THREAD_DETACH: {
//	}break;
//	case DLL_PROCESS_DETACH: {
//
//	}break;
//	}
//	return TRUE;
//}