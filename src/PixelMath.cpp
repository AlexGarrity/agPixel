#include "PixelMath.hpp"

#if defined(FOUND_AVX2)
// AVX is best, hopefully we can use it
#include "Math/PixelMathAVX.hpp"
#elif defined(FOUND_SSE2)
// If not, SSE2 will do
#include "Math/PixelMathSSE.hpp"
#else
// Guess we're out of luck
#include "Math/PixelMath.hpp"
#endif