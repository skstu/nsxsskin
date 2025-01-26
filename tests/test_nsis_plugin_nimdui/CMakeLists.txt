project(${entry_name})

GFN_PROJECT_SOURCE_GET(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

if(MSVC)
    add_compile_options(/wd4996 /wd4267)
    add_compile_options(/utf-8)
endif()

add_definitions(-DENABLE_BUILD_STATIC_WIN32 -DUSING_XS_SHARED)
add_executable(${PROJECT_NAME} ${SOURCES})

set(platform_name x64)
if(${CMAKE_VS_PLATFORM_NAME} STREQUAL "Win32")
  set(platform_name x86)
endif()

target_include_directories(${PROJECT_NAME}
PRIVATE 
${SOLUTION_INCLUDE_DIR}
${SOLUTION_ROOT_DIR}/3rdparty/fmt/include/
${SOLUTION_ROOT_DIR}/projects/win32/include/
${SOLUTION_ROOT_DIR}/3rdparty/dlfcn-win32/src/
${SOLUTION_ROOT_DIR}/projects/chromium/include/
)
  

target_link_directories(${PROJECT_NAME}
PRIVATE
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/
)

target_link_libraries(${PROJECT_NAME}
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/stl.lib
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/fmt.lib
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/win32.lib
)

if(MSVC)
MSVC_LINK_FLAGS_SET_CONSOLE(${PROJECT_NAME})
#MSVC_LINK_FLAGS_SET_WINDOWS(${PROJECT_NAME})
#MSVC_CRT_SET(${PROJECT_NAME} "/MT")
#MSVC_USE_PCH(${PROJECT_NAME} ${entry}/stdafx.h ${entry}/stdafx.cpp)
endif()