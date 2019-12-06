#include "PackedMath.hpp"

#if defined(FOUND_AVX)
#include "Math/PackedMathAVX.hpp"
#elif defined(FOUND_SSE2)
#include "Math/PackedMathSSE.hpp"
#else
#include "Math/PackedMathSSE.hpp"
#endif