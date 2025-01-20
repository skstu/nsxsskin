project(${entry_name})

GFN_PROJECT_SOURCE_GET(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

if(MSVC)
    add_compile_options(/wd4996 /wd4267)
    add_compile_options(/utf-8)
endif()

add_definitions(-DSHARED_IMPLEMENTATION)
add_definitions(-DENABLE_BUILD_STATIC_WIN32)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

#add_dependencies(${PROJECT_NAME} fmt stl win32)

target_include_directories(${PROJECT_NAME} 
PRIVATE
${SOLUTION_INCLUDE_DIR}
${SOLUTION_ROOT_DIR}/projects/win32/include/
${SOLUTION_ROOT_DIR}/3rdparty/fmt/include/
${SOLUTION_ROOT_DIR}/3rdparty/nimduilib/
)

SET(platform_name x64)
if(${CMAKE_VS_PLATFORM_NAME} STREQUAL "Win32")
SET(platform_name x86)
endif()

target_link_directories(${PROJECT_NAME}
PRIVATE
${SOLUTION_ROOT_DIR}/3rdparty/nimduilib/build_${platform_name}
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}
)

target_link_libraries(${PROJECT_NAME}
gdiplus
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/stl.lib
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/win32.lib
${SOLUTION_ROOT_DIR}/libs/${platform_name}/${VS_CONFIGURATION_TYPE}/fmt.lib
)

if(MSVC)
MSVC_LINK_FLAGS_SET_WINDOWS(${PROJECT_NAME})
if(ENABLE_MSVC_CRT_MT)
MSVC_CRT_SET(${PROJECT_NAME} "/MT")
endif(ENABLE_MSVC_CRT_MT)
MSVC_USE_PCH(${PROJECT_NAME} ${entry}/stdafx.h ${entry}/stdafx.cc)
endif()