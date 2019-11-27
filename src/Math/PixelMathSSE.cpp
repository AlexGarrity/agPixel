#include "Math/PixelMathSSE.hpp"

#include "PixelCore.hpp"
#include "PixelMath.hpp"

// Extensions are enabled, so use AVX2 rather than regular maths
namespace Pixel {

#define B(x) static_cast<BYTE>(x)
#define W(x) static_cast<WORD>(x)
#define D(x) static_cast<DWORD>(x)

// Some handy little helper functions for unpacking __mm256 types
BQuad UnpackChar(__m128i chars) {
  BQuad out;
  // These are cast as they sometimes come in as wider values
  out[0] = static_cast<BYTE>(chars[0]);
  out[1] = static_cast<BYTE>(chars[1] >> 16);
  out[2] = static_cast<BYTE>(chars[2]);
  out[3] = static_cast<BYTE>(chars[3] >> 16);
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

__m128i PackBQuad(BQuad b) {
  __m128i out;
  out[0] = D(b[0]) | D(b[1]) << 16;
  out[1] = D(b[2]) | D(b[3]) << 16;
  return out;
}

BQuad Add(BYTEQUAD) {
  __m128i a = PackBQuad(BQuad(a1, b1, c1, d1));
  __m128i b = PackBQuad(BQuad(a2, b2, c2, d2));
  auto result = _mm_adds_epu8(a, b);
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
  __m128i a = PackBQuad(BQuad(a1, b1, c1, d1));
  __m128i b = PackBQuad(BQuad(a2, b2, c2, d2));
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
  __m128i a = PackBQuad(BQuad(a1, b1, c1, d1));
  __m128i b = PackBQuad(BQuad(a2, b2, c2, d2));
  auto result = _mm_sub_epi16(a, b);
  return UnpackChar(result);
}

FQuad Sub(FLOATQUAD) {
  __m128 a{a1, b1, c1, d1};
  __m128 b{a2, b2, c2, d2};
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
  __m128 a{static_cast<float>(a1), static_cast<float>(b1),
           static_cast<float>(c1), static_cast<float>(d1)};
  __m128 b{static_cast<float>(a2), static_cast<float>(b2),
           static_cast<float>(c2), static_cast<float>(d2)};
  auto result = _mm_div_ps(a, b);
  return UnpackChar(result);
}

FQuad Div(FLOATQUAD) {
  __m128 a{a1, b1, c1, d1};
  __m128 b{a2, b2, c2, d2};
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