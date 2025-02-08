project(${entry_name})

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

if(MSVC)
  add_compile_options(/wd4996 /wd4267)
  add_compile_options(/utf-8)
endif()

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO /NODEFAULTLIB:libc.lib")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
add_definitions(-D_UNICODE -DUNICODE)
add_definitions(-DSHARED_IMPLEMENTATION)
add_definitions(-DENABLE_BUILD_STATIC_WIN32)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# add_dependencies(${PROJECT_NAME} fmt stl win32)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOLUTION_INCLUDE_DIR}
    ${SOLUTION_ROOT_DIR}/3rdparty/utfcpp/source/
    ${SOLUTION_ROOT_DIR}/projects/win32/include/
    ${SOLUTION_ROOT_DIR}/3rdparty/fmt/include/
    ${SOLUTION_ROOT_DIR}/3rdparty/DuiLib/
    ${SOLUTION_ROOT_DIR}/tools/NSIS/Examples/Plugin/nsis/)

set(platform_name x64)
if(${CMAKE_VS_PLATFORM_NAME} STREQUAL "Win32")
  set(platform_name x86)
endif()

target_link_directories(
  ${PROJECT_NAME} PRIVATE
  ${SOLUTION_ROOT_DIR}/tools/NSIS/Examples/Plugin/nsis
  ${SOLUTION_ROOT_DIR}/3rdparty/DuiLib/bin
  ${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE})

target_link_libraries(
  ${PROJECT_NAME}
  Msimg32.lib
  gdiplus.lib
  Imm32.lib
  ${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/zipcc.lib
  ${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/stl.lib
  ${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/win32.lib
  ${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/fmt.lib)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
    ${SOLUTION_ROOT_DIR}/tools/NSIS/Plugins/${platform_name}-unicode/${PROJECT_NAME}.dll)

if(MSVC)
  msvc_link_flags_set_windows(${PROJECT_NAME})
  if(ENABLE_MSVC_CRT_MT)
    msvc_crt_set(${PROJECT_NAME} "/MT")
  endif(ENABLE_MSVC_CRT_MT)
  msvc_use_pch(${PROJECT_NAME} ${entry}/stdafx.h ${entry}/stdafx.cc)
endif()
