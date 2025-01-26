cmake_minimum_required(VERSION 3.5)

project(zipcc)

set(xs3RDPARTY_DIR ${SOLUTION_ROOT_DIR}/3rdparty)
gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
if(WIN32)
set(SOURCES
    ${OUT_HEADER_S} ${OUT_SOURCE_S}
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/zip.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/unzip.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/ioapi.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/iowin32.c)
elseif(APPLE)
    set(SOURCES
    ${OUT_HEADER_S} ${OUT_SOURCE_S}
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/zip.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/unzip.c
    ${xs3RDPARTY_DIR}/zlib/contrib/minizip/ioapi.c)
endif()

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${SOLUTION_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
          ${xs3RDPARTY_DIR}/utfcpp/source/ ${xs3RDPARTY_DIR}/zlib/
          ${xs3RDPARTY_DIR}/zlib/contrib/minizip/)

#xs_set_target_output_dir(${PROJECT_NAME})

if(MSVC)
#MSVC_LINK_FLAGS_SET_CONSOLE(${PROJECT_NAME})
if(ENABLE_MSVC_CRT_MT)
MSVC_CRT_SET(${PROJECT_NAME} "/MT")
endif(ENABLE_MSVC_CRT_MT)
#MSVC_USE_PCH(${PROJECT_NAME} ${entry}/src/stdafx.h ${entry}/src/stdafx.cpp)
endif()