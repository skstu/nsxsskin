#include "stdafx.h"

BOOL APIENTRY DllMain(_In_ void* _DllHandle, _In_ unsigned long _Reason, _In_opt_ void* _Reserved) {
	switch (_Reason) {
	case DLL_PROCESS_ATTACH: {
#if defined(_DEBUG)
		::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//::_CrtSetBreakAlloc(162);
#endif
		auto current_path = shared::Win::GetModulePathA((HINSTANCE)_DllHandle);

		LOG_INIT(current_path + "nsxsskin.log");


	}break;
	case DLL_THREAD_ATTACH: {
	}break;
	case DLL_THREAD_DETACH: {
	}break;
	case DLL_PROCESS_DETACH: {
		LOG_UNINIT;
	}break;
	}
	return TRUE;
}