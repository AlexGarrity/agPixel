#include "Math/PixelMathAVX.hpp"

#include "PixelCore.hpp"
#include "PixelMath.hpp"

// Extensions are enabled, so use AVX2 rather than regular maths
namespace Pixel {

// Some handy little helper functions for unpacking __mm256 types
BQuad UnpackChar(__m128i chars) {
  BQuad out;
  // These are cast as they sometimes come in as wider values
  out[0] = static_cast<BYTE>(chars[0]);
  out[1] = static_cast<BYTE>(chars[1]);
  out[2] = static_cast<BYTE>(chars[2]);
  out[3] = static_cast<BYTE>(chars[3]);
  return out;
}

FQuad UnpackFloat(__m128 floats) {
  FQuad out;
  out[0] = floats[0];
  out[1] = floats[1];
  out[2] = floats[2];
  out[3] = floats[3];
  return out;
}

DQuad UnpackDouble(__m128d d1, __m128d d2) {
  DQuad out;
  out[0] = d1[0];
  out[1] = d1[1];
  out[2] = d2[0];
  out[3] = d2[1];
  return out;
}

BQuad Add(BYTEQUAD) {
  __m128i a{a1, b1, c1, d1};
  __m128i b{a2, b2, c2, d2};
  auto result = _mm_add_epu8(a, b);
  return UnpackChar(result);
}

FQuad Add(FLOATQUAD) {
  __m128 a{a1, b1, c1, d1};
  __m128 b{a2, b2, c2, d2};
  auto result = _mm_add_ps(a, b);
  return UnpackFloat(result);
}

DQuad Add(DOUBLEQUAD) {
  __m128d ax{a1, b1};
  __m128d ay{c1, d1};
  __m128d bx{a2, b2};
  __m128d by{c2, d2};
  auto r1 = _mm_add_pd(ax, bx);
  auto r2 = _mm_add_pd(ay, by);
  return UnpackDouble(r1, r2);
}

BQuad Mul(BYTEQUAD) {
  __m128i a{a1, b1, c1, d1};
  __m128i b{a1, b1, c1, d1};
  auto result = _mm_mul_epu32(a, b);
  return UnpackChar(result);
}

FQuad Mul(FLOATQUAD) {
  __m128 a{a1, b1, c1, d1};
  __m128 b{a2, b2, c2, d2};
  auto result = _mm_mul_ps(a, b);
  return UnpackFloat(result);
}

DQuad Mul(DOUBLEQUAD) {
  __m128d ax{a1, b1};
  __m128d ay{c1, d1};
  __m128d bx{a2, b2};
  __m128d by{c2, d2};
  auto r1 = _mm_mul_pd(ax, bx);
  auto r2 = _mm_mul_pd(ay, by);
  return UnpackDouble(r1, r2);
}

BQuad Sub(BYTEQUAD) {
  // There's no function for explicit subtraction, so we cast to 16-bit values
  // and add negatives
  __m128i a{static_cast<int16_t>(a1), static_cast<int16_t>(b1), static_cast<int16_t>(c1), static_cast<int16_t>(d1)};
  __m128i b{-static_cast<int16_t>(a2), -static_cast<int16_t>(b2), -static_cast<int16_t>(c2), -static_cast<int16_t>(d2)};
  auto result = _mm_add_epi16(a, b);
  return UnpackChar(result);
}

FQuad Sub(FLOATQUAD) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{a2, b2, c2, d2};
  auto result = _mm_sub_ps(a, b);
  return UnpackFloat(result);
}

DQuad Sub(DOUBLEQUAD) {
  __m128d ax{a1, b1};
  __m128d ay{c1, d1};
  __m128d bx{a2, b2};
  __m128d by{c2, d2};
  auto r1 = _mm_sub_pd(ax, bx);
  auto r2 = _mm_sub_pd(ay, by);
  return UnpackDouble(r1, r2);
}

BQuad Div(BYTEQUAD) {
    // This has to be done as floats, as integer division is unsupported
  __m256 a{static_cast<float>(a1), static_cast<float>(b1), static_cast<float>(c1), static_cast<float>(d1)};
  __m256 b{static_cast<float>(a2), static_cast<float>(b2), static_cast<float>(c2), static_cast<float>(d2)};
  auto result = _mm_div_ps(a, b);
  return UnpackChar(result);
}

FQuad Div(FLOATQUAD) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{a2, b2, c2, d2};
  auto result = _mm_div_ps(a, b);
  return UnpackFloat(result);
}

DQuad Div(DOUBLEQUAD) {
  __m128d ax{a1, b1};
  __m128d ay{c1, d1};
  __m128d bx{a2, b2};
  __m128d by{c2, d2};
  auto r1 = _mm_div_pd(ax, bx);
  auto r2 = _mm_div_pd(ay, by);
  return UnpackDouble(r1, r2);
}

} // namespace Pixel