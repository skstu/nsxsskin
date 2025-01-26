#include "stdafx.h"

BOOL APIENTRY DllMain(_In_ void* _DllHandle, _In_ unsigned long _Reason, _In_opt_ void* _Reserved) {
	switch (_Reason) {
	case DLL_PROCESS_ATTACH: {
		g_hInstance = (HINSTANCE)_DllHandle;
		//auto current_path = shared::Win::GetModulePathA((HINSTANCE)_DllHandle);
		//LOG_INIT(current_path + "nsxsskin.log");

		gpSignalSystemExit = new stl::Signal();
		Global::Get();
	}break;
	case DLL_THREAD_ATTACH: {
	}break;
	case DLL_THREAD_DETACH: {
	}break;
	case DLL_PROCESS_DETACH: {
		gpSignalSystemExit->notify();
		gpSignalSystemExit->Release();
		//LOG_UNINIT;
		Global::Destroy();
	}break;
	}
	return TRUE;
}