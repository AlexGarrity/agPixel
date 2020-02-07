#pragma once

#if defined(_MSC_VER)
// Windows DLL exporting
#ifdef BUILD_LIB
#define AG_API __declspec(dllexport)
#else
#define AG_API __declspec(dllimport)
#endif
#elif defined(__GNUC__)
// GCC exports everything anyway...
#ifdef BUILD_LIB
#define AG_API __attribute__((visibility("default")))
#else
#define AG_API
#endif
#else
#error Pixel is not supported on your platform
#endif
