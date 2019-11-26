cmake_minimum_required(VERSION 3.12)

project(libPixel VERSION 1.2 DESCRIPTION "Simple library for handling libPixels")
include(GNUInstallDirs)

set(BUILD_libPixel TRUE CACHE BOOL "Build the library")
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "Build the library shared (true) or static (false)")
set(ENABLE_EXTENSIONS FALSE CACHE BOOL "Enable the use of SIMD extensions")

if(${BUILD_libPixel})
    set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS} "BUILD_LIB")
endif()

if(${BUILD_SHARED_LIBS})
    set (LIBRARY_KEYWORD "SHARED")
else()
    set (LIBRARY_KEYWORD "STATIC")
endif()

set(SOURCE
    ${CMAKE_SOURCE_DIR}/src/PixelDouble.cpp
    ${CMAKE_SOURCE_DIR}/src/PixelFloat.cpp
    ${CMAKE_SOURCE_DIR}/src/PixelInt.cpp
    ${CMAKE_SOURCE_DIR}/src/PixelMath.cpp
)

if(${ENABLE_EXTENSIONS})
    # Enable the AVX versions of PixelMath and PixelPackedMath
    set(MATH_SOURCE
        ${CMAKE_SOURCE_DIR}/src/Math/PixelMathAVX.cpp
    )
    set(PACKED_MATH_SOURCE
        ${CMAKE_SOURCE_DIR}/src/Math/PixelPackedMathAVX.cpp
    )
    # Define the stuff we need to turn extensions on
    set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS} "ENABLE_EXTENSIONS")
    set(EXTRA_COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS} "-mavx2")
else()
    # Enable the vanilla versions of PixelMath and PixelPackedMath
    set(MATH_SOURCE
        ${CMAKE_SOURCE_DIR}/src/Math/PixelMath.cpp
    )
    set(PACKED_MATH_SOURCE
        ${CMAKE_SOURCE_DIR}/src/Math/PixelPackedMath.cpp
    )
    set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS})
    set(EXTRA_COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS})
    # No extra definitions needed.  Vanilla C++
endif()

add_library(
    libPixel ${LIBRARY_KEYWORD} ${SOURCE} ${MATH_SOURCE} ${PACKED_MATH_SOURCE}
)
if(NOT "${EXTRA_COMPILE_DEFS}" STREQUAL "")
    add_compile_definitions(${EXTRA_COMPILE_DEFS})
endif()
if(NOT "${EXTRA_COMPILE_FLAGS}" STREQUAL "")
    set_target_properties(libPixel PROPERTIES COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS})
endif()

set_target_properties(
    libPixel PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    PREFIX ""
)

target_include_directories(
    libPixel PRIVATE ${CMAKE_SOURCE_DIR}/include
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
