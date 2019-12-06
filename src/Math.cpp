#include "Math.hpp"

#if defined(FOUND_AVX2)
// AVX is best, hopefully we can use it
#include "Math/MathAVX.hpp"
#elif defined(FOUND_SSE2)
// If not, SSE2 will do
#include "Math/MathSSE.hpp"
#else
// Guess we're out of luck
#include "Math/Math.hpp"
#endif