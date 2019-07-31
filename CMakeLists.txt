
# The following guide was a massive help:
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
# By that, I mean I pretty much copied it
# Thanks @Jezz

cmake_minimum_required(VERSION 3.12)

project(Pixel VERSION 1.0 DESCRIPTION "Simple library for handling pixels")
include(GNUInstallDirs)

set(BUILD_SHARED_LIBS true CACHE BOOL "Build the library")
set(ENABLE_EXTENSIONS true CACHE BOOL "Enable the use of SIMD extensions")

if(${BUILD_SHARED_LIBS})
add_compile_definitions("BUILD_LIB")
endif()

if(${ENABLE_EXTENSIONS})
add_compile_definitions("ENABLE_EXTENSIONS")
endif()

add_library(Pixel SHARED
    src/PixelInt.cpp
    src/PixelFloat.cpp
    src/PixelDouble.cpp
    src/PixelMath.cpp
)

set_target_properties(Pixel PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(
    Pixel PRIVATE include
    Pixel PRIVATE src
)

install(TARGETS Pixel
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)