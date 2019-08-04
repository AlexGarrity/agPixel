
# The following guide was a massive help:
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
# By that, I mean I pretty much copied it
# Thanks @Jezz

cmake_minimum_required(VERSION 3.12)

project(Pixel VERSION 1.1 DESCRIPTION "Simple library for handling pixels")
include(GNUInstallDirs)

set(BUILD_PIXEL TRUE CACHE BOOL "Build the library")
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "Build the library shared (true) or static (false)")
set(ENABLE_EXTENSIONS FALSE CACHE BOOL "Enable the use of SIMD extensions")

if(${BUILD_PIXEL})
add_compile_definitions("BUILD_LIB")
endif()

if(${BUILD_SHARED_LIBS})
set (LIBRARY_KEYWORD "SHARED")
else()
set (LIBRARY_KEYWORD "STATIC")
endif()

add_library(Pixel ${LIBRARY_KEYWORD}
    src/PixelInt.cpp
    src/PixelFloat.cpp
    src/PixelDouble.cpp
    src/PixelMath.cpp
)

set_target_properties(Pixel PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

if(${ENABLE_EXTENSIONS})
add_compile_definitions("ENABLE_EXTENSIONS")
set_target_properties(Pixel PROPERTIES COMPILE_FLAGS "-mavx2")
endif()

target_include_directories(
    Pixel PRIVATE include
    Pixel PRIVATE src
)

install(TARGETS Pixel
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)