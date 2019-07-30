
# The following guide was a massive help:
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
# By that, I mean I pretty much copied it
# Thanks @Jezz

cmake_minimum_required(VERSION 3.10)

project(libPixel VERSION 1.0 DESCRIPTION "Simple library for handling images")
include(GNUInstallDirs)

add_library(libPixel SHARED
    src/PixelInt.cpp
    src/PixelFloat.cpp
)

set_target_properties(libPixel PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_include_directories(
    libPixel PRIVATE include
    libPixel PRIVATE src
)



install(TARGETS libPixel
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES ${CMAKE_BINARY_DIR}/libPixel.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)