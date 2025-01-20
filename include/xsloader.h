#if !defined(__4405260B_F11E_4BE7_86CB_E1878100C9C8__)
#define __4405260B_F11E_4BE7_86CB_E1878100C9C8__

#ifdef __cplusplus
extern "C" {
#endif

	/* Referenced C standard library header files */
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Interface definition */
#if defined(BUILDING_XS_SHARED) && defined(USING_XS_SHARED)
#error "Define either BUILDING_XS_SHARED or USING_XS_SHARED, not both."
#endif

#ifndef XS_EXTERN
#ifdef _WIN32
/* Windows - set up dll import/export decorators. */
#if defined(BUILDING_XS_SHARED)
/* Building shared library. */
#define XS_EXTERN __declspec(dllexport)
#elif defined(USING_XS_SHARED)
/* Using shared library. */
#define XS_EXTERN __declspec(dllimport)
#else
/* Building static library. */
#define XS_EXTERN /* nothing */
#endif
#elif __GNUC__ >= 4
#define XS_EXTERN __attribute__((visibility("default")))
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550) /* Sun Studio >= 8 */
#define XS_EXTERN __global
#else
#define XS_EXTERN /* nothing */
#endif
#endif /* XS_EXTERN */

	typedef void* (*xs_malloc_func)(size_t size);
	typedef void* (*xs_realloc_func)(void* ptr, size_t size);
	typedef void* (*xs_calloc_func)(size_t count, size_t size);
	typedef void (*xs_free_func)(void* ptr);

	//!@ handles
	typedef unsigned long long xs_unitptr;
	typedef void* xs_handle_t;
	typedef void* xs_route_ptr_t;
	typedef void* xs_common_callback;

	typedef void(*xs_callback_startup_result)(int r, xs_route_ptr_t route);

#if 0
	typedef void* xs_handle_t;
	typedef void* xs_common_callback;
	typedef void(*tf_xs_free_s)(void**);
	typedef const char* (*tf_xs_err_name)(int);
	typedef const char* (*tf_xs_err_string)(int);
	typedef int(*tf_xs_startup)(xs_callback_startup_result, xs_handle_t*);
	typedef void(*tf_xs_shutdown)(void);
	typedef int(*tf_xs_component_get_handle)(const char*, xs_handle_t*);
	typedef int(*tf_xs_componect_get_hmodule)(const char*, xs_handle_t*);

	typedef int(*tf_xs_get_plugin_module_handle)(const char*, xs_handle_t*);
	typedef int(*tf_xs_get_componect_module_handle)(const char*, xs_handle_t*);
#endif

	XS_EXTERN int xs_startup(xs_callback_startup_result result_cb, xs_route_ptr_t route);
	XS_EXTERN void xs_shutdown(void);
	XS_EXTERN int xs_componect_get_hmodule_unitptr(const char* name, xs_unitptr* output_module_handle);
	XS_EXTERN int xs_componect_get_hmodule(const char* name, xs_handle_t* output_module_handle);
	XS_EXTERN int xs_componect_get_proc_address(const char* comp_name, const char* fun_name, xs_unitptr* output_fun_address);
	XS_EXTERN unsigned int xs_version(void);
	XS_EXTERN const char* xs_version_string(void);
	XS_EXTERN void xs_free_s(void**);
	XS_EXTERN const char* xs_err_name(int err);
	XS_EXTERN const char* xs_err_string(int err);
	XS_EXTERN int xs_get_handle(xs_handle_t* current_module_handle);
	XS_EXTERN int xs_handle_to_hmodule(xs_handle_t input_handle, xs_handle_t* output_module_handle/*Window HMODULE*/);
	XS_EXTERN int xs_componect_get_handle(const char* name, xs_handle_t* componect_module_handle);
	XS_EXTERN int xs_componect_register_callback_form_key(const char* name, xs_common_callback);
	XS_EXTERN int xs_componect_register_callback_from_handle(xs_handle_t* input_componect_handle, xs_common_callback input_cb);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	XS_EXTERN int xs_get_plugin_module_handle(const char* module_name, xs_handle_t* module_handle);
	XS_EXTERN int xs_get_componect_module_handle(const char* module_name, xs_handle_t* module_handle);
#ifdef __cplusplus
}//extern "C" {
#endif

/// /*_ Memade®（新生™） _**/
/// /*_ Mon, 16 Sep 2024 09:42:31 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__4405260B_F11E_4BE7_86CB_E1878100C9C8__
