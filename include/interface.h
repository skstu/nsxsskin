#ifndef _INTERFACE_H__
#define _INTERFACE_H__

#if defined(_WIN32)
#if defined(SHARED_IMPLEMENTATION)
#define SHARED_API __declspec(dllexport)
#define SHARED_API_PRIVATE __declspec(dllexport)
#else
#define SHARED_API __declspec(dllimport)
#define SHARED_API_PRIVATE __declspec(dllimport)
#endif // defined(SHARED_IMPLEMENTATION)
#else  // _WIN32
#if defined(SHARED_IMPLEMENTATION)
#define SHARED_API __attribute__((visibility("default")))
#define SHARED_API_PRIVATE __attribute__((visibility("default")))
#else
#define SHARED_API
#define SHARED_API_PRIVATE
#endif // defined(SHARED_IMPLEMENTATION)
#endif // _WIN32

using tf_interface_init = void* (*)(void*, unsigned long);
using tf_interface_uninit = void (*)(void);
const char name_interface_init[] = "interface_init";
const char name_interface_uninit[] = "interface_uninit";

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <string.h>

template <typename T> class Interface {
public:
#ifdef _WIN32
	static T* GetFromModuleHandle(const char* module_name) {
		T* result = nullptr;
		tf_interface_init init_ = nullptr;
		do {
			if (!module_name)
				break;
			HMODULE hModule = GetModuleHandleA(module_name);
			if (!hModule)
				break;
			init_ = decltype(init_)(
				GetProcAddress(hModule, name_interface_init));
			if (!init_)
				break;
			result = (T*)init_((void*)hModule, static_cast<unsigned long>(sizeof(hModule)));
		} while (0);
		return result;
	}
#endif//!@ _WIN32

	static T* Create(const char* dyPathname) {
		T* result = nullptr;
		void* handle_ = nullptr;
		tf_interface_init init_ = nullptr;
		tf_interface_uninit uninit_ = nullptr;
		do {
			if (!dyPathname) {
				break;
			}
#ifdef _WIN32
			handle_ = (void*)LoadLibraryA(dyPathname);
#else
			handle_ = dlopen(dyPathname, /*RTLD_NOW*/ RTLD_LAZY);
#endif
			if (!handle_)
				break;
#ifdef _WIN32
			init_ = decltype(init_)(
				GetProcAddress((HMODULE)handle_, name_interface_init));
			uninit_ = decltype(uninit_)(
				GetProcAddress((HMODULE)handle_, name_interface_uninit));
#else
			init_ = decltype(init_)(dlsym(handle_, name_interface_init));
			uninit_ = decltype(uninit_)(dlsym(handle_, name_interface_uninit));
#endif
			if (!init_ || !uninit_) {
				break;
			}
			result = (T*)init_((void*)dyPathname, static_cast<unsigned long>(strlen(dyPathname)));
			if (!result) {
				uninit_();
				break;
			}
			result->handle_ = handle_;
			result->interface_init_ = init_;
			result->interface_uninit_ = uninit_;
#ifdef _WIN32
			strcpy_s(result->module_filename_, dyPathname);
#else
			strcpy(result->module_filename_, dyPathname);
#endif
		} while (0);
		if (!result && handle_) {
#ifdef _WIN32
			FreeLibrary((HMODULE)handle_);
#else
			dlclose(handle_);
#endif
			handle_ = nullptr;
		}
		return result;
	}
	static void Destroy(T** obj) {
		do {
			if (!(*obj)) {
				break;
			}
			Interface* _this = (Interface*)(*obj);
			if (!_this) {
				break;
			}
			void* htmp = _this->handle_;
			if (_this->interface_uninit_) {
				_this->interface_uninit_();
			}
			if (htmp) {
#ifdef _WIN32
				FreeLibrary((HMODULE)htmp);
#else
				dlclose(htmp);
#endif
			}
			*obj = nullptr;
		} while (0);
	}

private:
	tf_interface_init interface_init_ = nullptr;
	tf_interface_uninit interface_uninit_ = nullptr;
public:
	void* ModuleHandle() const {
		return handle_;
	}
protected:
	void* handle_ = nullptr;
	char module_filename_[260] = { 0 };
};

#endif // _INTERFACE_H__
