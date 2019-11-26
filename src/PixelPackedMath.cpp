#include "PixelPackedMath.hpp"

#if defined(FOUND_AVX)
    #include "Math/PixelPackedMathAVX.hpp"
#else
    #include "Math/PixelPackedMathRegular.hpp"
#endif