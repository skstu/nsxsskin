cmake_minimum_required(VERSION 3.12)
project (nsxsskin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOLUTION_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set(LOCAL_CMAKE_MODULES_PATH ${SOLUTION_ROOT_DIR}/cmake/modules/)
set(SOLUTION_INCLUDE_DIR ${SOLUTION_ROOT_DIR}/include/)

set(CMAKE_BINARY_DIR ${SOLUTION_ROOT_DIR}/cmake_build/)


if(CMAKE_CONFIGURATION_TYPES)
  set(VS_CONFIGURATION_TYPE $<CONFIG>)
else()
  set(VS_CONFIGURATION_TYPE ${CMAKE_BUILD_TYPE})
endif()


LIST(APPEND CMAKE_MODULE_PATH ${LOCAL_CMAKE_MODULES_PATH})
include(global)

if(MSVC)
include(msvc)
option(ENABLE_MSVC_CRT_MT "Enable msvc crt /MT /MTd compile." ON)
option(ENABLE_BUILD_STATIC_WIN32 "Enable build static win32 library." ON)
endif(MSVC)

add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;" CACHE STRING "info" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

# 3rdparty
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(FMT_DEBUG_POSTFIX "" CACHE STRING "FMT Debug libray postfix" FORCE)
GFN_SET_TARGET_OUTDIR(${SOLUTION_ROOT_DIR} "bin" "objs" "libs")

#set(CMAKE_DEBUG_POSTFIX "" CACHE STRING "" FORCE)
set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "disabled zlib build examples." FORCE)
add_subdirectory(${SOLUTION_ROOT_DIR}/3rdparty/zlib/ "zlib")
set_target_properties(zlibstatic PROPERTIES FOLDER "3rdparty")
set_target_properties(zlib PROPERTIES FOLDER "3rdparty")

set(FMT_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${SOLUTION_ROOT_DIR}/3rdparty/fmt/ "fmt")
set_target_properties(fmt PROPERTIES FOLDER "3rdparty")

set(CMAKE_DEBUG_POSTFIX
    ""
    CACHE STRING "..." FORCE)
add_subdirectory(${SOLUTION_ROOT_DIR}/3rdparty/minizip/ minizip)

GFN_SET_TARGET_OUTDIR("")

if(MSVC AND ENABLE_MSVC_CRT_MT)

#set(VCPKG_ROOT C:\/Users\/k34ub\/source\/vcpkg\/)
#set(VCPKG_ROOT F:\/vcpkg\/)
set(VCPKG_ROOT F:\/vcpkg\/)
#set(VCPKG_ROOT C:\/vcpkg-static\/)
MSVC_CRT_SET(fmt "/MT")
MSVC_CRT_SET(zlib "/MT")
MSVC_CRT_SET(zlibstatic "/MT")
else()
set(VCPKG_ROOT C:\/Users\/k34ub\/source\/vcpkg\/)
#set(VCPKG_ROOT F:\/vcpkg\/)
endif(MSVC AND ENABLE_MSVC_CRT_MT)

#[[
OutputPathConfig("bin" "libs/runtimes/" "libs/runtimes/")
add_subdirectory(${SOLUTION_ROOT_DIR}/runtimes/)
OutputPathConfig("")
option(ENABLE_MAIN_PROJECT_COMPILE_TESTS "Enable main projcet tests compile." ON)
if(ENABLE_MAIN_PROJECT_COMPILE_TESTS)
OutputPathConfig("bin" "bin/tests/" "objs")
add_subdirectory(${SOLUTION_ROOT_DIR}/tests/)
#set_target_properties(tests PROPERTIES FOLDER "tests")
OutputPathConfig("")
endif(ENABLE_MAIN_PROJECT_COMPILE_TESTS)
]]
#[[
]]

#add_subdirectory(${SOLUTION_ROOT_DIR}/tools/)

add_subdirectory(${SOLUTION_ROOT_DIR}/tests/)
#set_target_properties(tests PROPERTIES FOLDER "tests")

add_subdirectory(${SOLUTION_ROOT_DIR}/projects/)

