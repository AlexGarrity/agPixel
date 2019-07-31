#include "PixelMath.hpp"

#if defined(ENABLE_EXTENSIONS)
// Extensions are enabled, so use AVX2 rather than regular maths

char *Add(char a1, char a2, char b1, char b2, char c1, char c2, char d1, char d2) {
    // Pack the chars into an __m256i...
    __m256i v {};


    // Unpack and return
    auto *out = new char[4];
    return out;
}

#else

char *Add(char a1, char a2, char b1, char b2, char c1, char c2, char d1, char d2) {
    char *out = new char[4];
    out[0] = a1 + a1;
    out[1] = b1 + b2;
    out[2] = c1 + c2;
    out[3] = d1 + d2;
    return out;
}
#endif