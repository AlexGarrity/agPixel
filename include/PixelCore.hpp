#pragma once

#if defined(_MSC_VER)
    // Windows DLL exporting
    #ifdef BUILD_LIB
        #define PIXEL_API __declspec(dllexport)
    #else
        #define PIXEL_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__)
    // GCC exports everything anyway...
    #ifdef BUILD_LIB
        #define PIXEL_API __attribute__((visibility("default")))
    #else
        #define PIXEL_API
    #endif
#else
    #error libPixel is not supported on your platform
#endif

#if defined(ENABLE_EXTENSIONS)
    #if defined(__AVX2__)
        #include <immintrin.h>
    #else
        // No AVX2 support, so we can't use extensions
        #undef ENABLE_EXTENSIONS
        #warning "Extensions have been enabled, but aren't available - continuing without"
    #endif
#endif