#include "Math/PixelMathAVX.hpp"

#include "PixelCore.hpp"
#include "PixelMath.hpp"

// Extensions are enabled, so use AVX2 rather than regular maths
namespace Pixel {

// Some handy little helper functions for unpacking __mm256 types
BQuad UnpackChar(__m256i chars) {
  BQuad out;
  // These are cast as they sometimes come in as wider values
  out[0] = static_cast<BYTE>(chars[0]);
  out[1] = static_cast<BYTE>(chars[1]);
  out[2] = static_cast<BYTE>(chars[2]);
  out[3] = static_cast<BYTE>(chars[3]);
  return out;
}

FQuad UnpackFloat(__m256 floats) {
  FQuad out;
  out[0] = floats[0];
  out[1] = floats[1];
  out[2] = floats[2];
  out[3] = floats[3];
  return out;
}

DQuad UnpackDouble(__m256d doubles) {
  DQuad out;
  out[0] = doubles[0];
  out[1] = doubles[1];
  out[2] = doubles[2];
  out[3] = doubles[3];
  return out;
}

BQuad Add(BYTEQUAD) {
  __m256i a{a1, b1, c1, d1};
  __m256i b{a2, b2, c2, d2};
  auto result = _mm256_adds_epu8(a, b);
  return UnpackChar(result);
}

FQuad Add(FLOATQUAD) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{a2, b2, c2, d2};
  auto result = _mm256_add_ps(a, b);
  return UnpackFloat(result);
}

DQuad Add(DOUBLEQUAD) {
  __m256d a{a1, b1, c1, d1};
  __m256d b{a2, b2, c2, d2};
  auto result = _mm256_add_pd(a, b);
  return UnpackDouble(result);
}

BQuad Mul(BYTEQUAD) {
  __m256i a{a1, b1, c1, d1};
  __m256i b{a1, b1, c1, d1};
  auto result = _mm256_mul_epu32(a, b);
  return UnpackChar(result);
}

FQuad Mul(FLOATQUAD) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{a2, b2, c2, d2};
  auto result = _mm256_mul_ps(a, b);
  return UnpackFloat(result);
}

DQuad Mul(DOUBLEQUAD) {
  __m256d a{a1, b1, c1, d1};
  __m256d b{a2, b2, c2, d2};
  auto result = _mm256_mul_pd(a, b);
  return UnpackDouble(result);
}

BQuad Sub(BYTEQUAD) {
  // There's no function for explicit subtraction, so we cast to 16-bit values
  // and add negatives
  __m256i a{a1, b1, c1, d1};
  __m256i b{-a2, -b2, -c2, -d2};
  auto result = _mm256_adds_epi16(a, b);
  return UnpackChar(result);
}

FQuad Sub(FLOATQUAD) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{-a2, -b2, -c2, -d2};
  auto result = _mm256_add_ps(a, b);
  return UnpackFloat(result);
}

DQuad Sub(DOUBLEQUAD) {
  __m256d a{a1, b1, c1, d1};
  __m256d b{a2, b2, c2, d2};
  auto result = _mm256_add_pd(a, b);
  return UnpackDouble(result);
}

BQuad Div(BYTEQUAD) {
  __m256i a{a1, b1, c1, d1};
  __m256i b{1 / a2, 1 / b2, 1 / c2, 1 / d2};
  auto result = _mm256_mul_epu32(a, b);
  return UnpackChar(result);
}

FQuad Div(FLOATQUAD) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{a2, b2, c2, d2};
  auto result = _mm256_div_ps(a, b);
  return UnpackFloat(result);
}

DQuad Div(DOUBLEQUAD) {
  __m256d a{a1, b1, c1, d1};
  __m256d b{a2, b2, c2, d2};
  auto result = _mm256_div_pd(a, b);
  return UnpackDouble(result);
}

} // namespace Pixel