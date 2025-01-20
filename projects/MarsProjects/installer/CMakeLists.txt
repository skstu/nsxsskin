project(${entry_name})

GFN_PROJECT_SOURCE_GET(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

if(MSVC)
    add_compile_options(/wd4996 /wd4267)
    add_compile_options(/utf-8)
endif()

add_definitions(-DSHARED_IMPLEMENTATION)
add_definitions(-DENABLE_BUILD_STATIC_WIN32)
add_definitions(-DBUILDING_CHROMIUM_SHARED)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PRIVATE
${SOLUTION_INCLUDE_DIR}
${SOLUTION_ROOT_DIR}/projects/chromium/include/
${SOLUTION_ROOT_DIR}/projects/win32/include/
${SOLUTION_ROOT_DIR}/3rdparty/fmt/include/
${SOLUTION_ROOT_DIR}/3rdlocal/zlib/
${SOLUTION_ROOT_DIR}/3rdlocal/zlib/contrib/minizip/
${SOLUTION_ROOT_DIR}/3rdlocal/nimduilib/
${SOLUTION_ROOT_DIR}/3rdlocal/cpp-httplib/
${SOLUTION_ROOT_DIR}/3rdlocal/http-parser/
)


target_link_directories(${PROJECT_NAME}
PRIVATE
${SOLUTION_ROOT_DIR}/3rdlocal/nimduilib/libs/
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/
)

target_link_libraries(${PROJECT_NAME}
gdiplus
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/stl.lib
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/win32.lib
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/fmt.lib
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/zipcc.lib
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/minizip.lib
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/bit7z.lib
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/http_parser.lib
${SOLUTION_ROOT_DIR}/libs/${CMAKE_VS_PLATFORM_NAME}/${VS_CONFIGURATION_TYPE}/libchromium.lib
)

if(MSVC)
MSVC_LINK_FLAGS_SET_WINDOWS(${PROJECT_NAME})
if(ENABLE_MSVC_CRT_MT)
MSVC_CRT_SET(${PROJECT_NAME} "/MT")
endif(ENABLE_MSVC_CRT_MT)
MSVC_USE_PCH(${PROJECT_NAME} ${entry}/stdafx.h ${entry}/stdafx.cc)
endif()