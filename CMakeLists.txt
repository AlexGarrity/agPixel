
# The following guide was a massive help:
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
# By that, I mean I pretty much copied it
# Thanks @Jezz

cmake_minimum_required(VERSION 3.12)

project(libPixel VERSION 1.1 DESCRIPTION "Simple library for handling libPixels")
include(GNUInstallDirs)

set(BUILD_libPixel TRUE CACHE BOOL "Build the library")
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "Build the library shared (true) or static (false)")
set(ENABLE_EXTENSIONS FALSE CACHE BOOL "Enable the use of SIMD extensions")

if(${BUILD_libPixel})
    add_compile_definitions("BUILD_LIB")
endif()

if(${BUILD_SHARED_LIBS})
    set (LIBRARY_KEYWORD "SHARED")
else()
    set (LIBRARY_KEYWORD "STATIC")
endif()

add_library(
    libPixel ${LIBRARY_KEYWORD}
    src/PixelInt.cpp
    src/PixelFloat.cpp
    src/PixelDouble.cpp
    src/PixelMath.cpp
)

set_target_properties(
    libPixel PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PREFIX ""
)

if(${ENABLE_EXTENSIONS})
    add_compile_definitions("ENABLE_EXTENSIONS")
    set_target_properties(libPixel PROPERTIES COMPILE_FLAGS "-mavx2")
endif()

target_include_directories(
    libPixel PUBLIC include
)

install(
    TARGETS libPixel
    EXPORT libPixelConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT libPixelConfig
    NAMESPACE libPixel::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libPixel
)

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libPixel
)
