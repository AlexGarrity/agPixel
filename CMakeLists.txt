cmake_minimum_required(VERSION 3.12)

project(Pixel VERSION 2.0.0 DESCRIPTION "Simple library for handling Pixels")
include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)

find_package(agSIMD REQUIRED)

message(STATUS "Using agPixel Version ${PROJECT_VERSION}")

set(BUILD_agPixel TRUE CACHE BOOL "Build the library")
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "Build the library shared (true) or static (false)")

if(${BUILD_agPixel})
    set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS} "BUILD_LIB")
endif()

if(${BUILD_SHARED_LIBS})
    set (LIBRARY_KEYWORD "SHARED")
else()
    set (LIBRARY_KEYWORD "STATIC")
endif()

add_subdirectory(agPixel)