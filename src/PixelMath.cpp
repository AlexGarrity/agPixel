#include "PixelMath.hpp"

#if defined(FOUND_AVX)
#include "Math/PixelMathAVX.hpp"
#else
#include "Math/PixelMath.hpp"
#endif