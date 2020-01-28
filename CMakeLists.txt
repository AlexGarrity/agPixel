cmake_minimum_required(VERSION 3.12)

project(agPixel VERSION 1.2.4 DESCRIPTION "Simple library for handling Pixels")
include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "Using agPixel Version ${PROJECT_VERSION}")

set(BUILD_agPixel TRUE CACHE BOOL "Build the library")
set(BUILD_SHARED_LIBS TRUE CACHE BOOL "Build the library shared (true) or static (false)")
set(ENABLE_EXTENSIONS FALSE CACHE BOOL "Enable the use of SIMD extensions")

if(${BUILD_agPixel})
    set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS} "BUILD_LIB")
endif()

if(${BUILD_SHARED_LIBS})
    set (LIBRARY_KEYWORD "SHARED")
else()
    set (LIBRARY_KEYWORD "STATIC")
endif()

set(SOURCE
    # Pixel sources
    ${CMAKE_SOURCE_DIR}/src/Pixel/Double.cpp
    ${CMAKE_SOURCE_DIR}/src/Pixel/Float.cpp
    ${CMAKE_SOURCE_DIR}/src/Pixel/Int.cpp
    # Pixel array sources
    ${CMAKE_SOURCE_DIR}/src/Array/Double.cpp
    ${CMAKE_SOURCE_DIR}/src/Array/Float.cpp
    ${CMAKE_SOURCE_DIR}/src/Array/Int.cpp
    # Math sources
    ${CMAKE_SOURCE_DIR}/src/PackedMath.cpp
    ${CMAKE_SOURCE_DIR}/src/Math.cpp
)

if(${ENABLE_EXTENSIONS})

    message(NOTICE "Vector extensions have been enabled")
    # Check if we have either SSE2 or AVX2
    set(HAS_AVX2 -1)
    set(HAS_SSE2 -1)

    # AVX2 Check goes here
    include(${CMAKE_SOURCE_DIR}/cmake/TestAVX2.cmake)
    include(${CMAKE_SOURCE_DIR}/cmake/TestSSE2.cmake)
    
    

    TestAVX2()
    if("${HAS_AVX2}" STREQUAL "0")
        message(NOTICE "CPU supports AVX2, enabling AVX2 maths")
        # Enable the AVX versions of PixelMath and PixelPackedMath
        set(MATH_SOURCE
            ${CMAKE_SOURCE_DIR}/src/Math/MathAVX.cpp
        )
        set(PACKED_MATH_SOURCE
            ${CMAKE_SOURCE_DIR}/src/Math/PackedMathAVX.cpp
        )
        # Define the stuff we need to turn extensions on
        set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS} "ENABLE_EXTENSIONS" "FOUND_AVX2")
        set(EXTRA_COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS} ${AVX2_FLAG})
    else()
        TestSSE2()
        if("${HAS_SSE2}" STREQUAL "0")
            message(NOTICE "CPU supports SSE2, enabling SSE2 maths")
            # Enable the AVX versions of PixelMath and PixelPackedMath
            set(MATH_SOURCE
                ${CMAKE_SOURCE_DIR}/src/Math/MathSSE.cpp
            )
            set(PACKED_MATH_SOURCE
                ${CMAKE_SOURCE_DIR}/src/Math/PackedMathSSE.cpp
            )
            # Define the stuff we need to turn extensions on
            set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS} "ENABLE_EXTENSIONS" "FOUND_SSE2")
            set(EXTRA_COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS} ${SSE2_FLAG})
        else()
            message(FATAL_ERROR "Extensions have been enabled but the CPU does not support them.  Please reconfigure the project.")
        endif()
    endif()

else()
    # Enable the vanilla versions of PixelMath and PixelPackedMath
    message(NOTICE "Extensions not enabled, using vanilla maths")
    set(MATH_SOURCE
        ${CMAKE_SOURCE_DIR}/src/Math/Math.cpp
    )
    set(PACKED_MATH_SOURCE
        ${CMAKE_SOURCE_DIR}/src/Math/PackedMath.cpp
    )
    set(EXTRA_COMPILE_DEFS ${EXTRA_COMPILE_DEFS})
    set(EXTRA_COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS})
    # No extra definitions needed.  Vanilla C++
endif()

add_library(
    agPixel ${LIBRARY_KEYWORD} ${SOURCE} ${MATH_SOURCE} ${PACKED_MATH_SOURCE}
)
if(NOT "${EXTRA_COMPILE_DEFS}" STREQUAL "")
    add_compile_definitions(${EXTRA_COMPILE_DEFS})
endif()
if(NOT "${EXTRA_COMPILE_FLAGS}" STREQUAL "")
    set_target_properties(agPixel PROPERTIES COMPILE_FLAGS ${EXTRA_COMPILE_FLAGS})
endif()

set_target_properties(
    agPixel PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
    PREFIX ""
)

target_include_directories(
    agPixel PRIVATE ${CMAKE_SOURCE_DIR}/include
)

install(
    TARGETS agPixel
    EXPORT agPixelConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT agPixelConfig
    NAMESPACE agPixel::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/agPixel
)

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/agPixel
)
