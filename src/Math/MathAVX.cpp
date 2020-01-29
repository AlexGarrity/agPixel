#include "Math/MathAVX.hpp"

#include "Core.hpp"
#include "Math.hpp"

// Extensions are enabled, so use AVX2 rather than regular maths
namespace ag {
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
  __m256i a{a1, b1, c1, d1};
  __m256i b{a2, b2, c2, d2};
  auto result = _mm256_sub_epi16(a, b);
  return UnpackChar(result);
}

FQuad Sub(FLOATQUAD) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{a2, b2, c2, d2};
  auto result = _mm256_sub_ps(a, b);
  return UnpackFloat(result);
}

DQuad Sub(DOUBLEQUAD) {
  __m256d a{a1, b1, c1, d1};
  __m256d b{a2, b2, c2, d2};
  auto result = _mm256_sub_pd(a, b);
  return UnpackDouble(result);
}

BQuad Div(BYTEQUAD) {
  __m256 a{static_cast<float>(a1), static_cast<float>(b1),
           static_cast<float>(c1), static_cast<float>(d1)};
  __m256 b{static_cast<float>(a2), static_cast<float>(b2),
           static_cast<float>(c2), static_cast<float>(d2)};
  auto result = _mm256_div_ps(a, b);
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

BQuad Add(BQUADPAIR) {
  __m256i a{qA[0], qA[1], qA[2], qA[3]};
  __m256i b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_adds_epu8(a, b);
  return UnpackChar(result);
}

FQuad Add(FQUADPAIR) {
  __m256 a{qA[0], qA[1], qA[2], qA[3]};
  __m256 b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_add_ps(a, b);
  return UnpackFloat(result);
}

DQuad Add(DQUADPAIR) {
  __m256d a{qA[0], qA[1], qA[2], qA[3]};
  __m256d b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_add_pd(a, b);
  return UnpackDouble(result);
}

BQuad Mul(BQUADPAIR) {
  __m256i a{qA[0], qA[1], qA[2], qA[3]};
  __m256i b{qA[0], qA[1], qA[2], qA[3]};
  auto result = _mm256_mul_epu32(a, b);
  return UnpackChar(result);
}

FQuad Mul(FQUADPAIR) {
  __m256 a{qA[0], qA[1], qA[2], qA[3]};
  __m256 b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_mul_ps(a, b);
  return UnpackFloat(result);
}

DQuad Mul(DQUADPAIR) {
  __m256d a{qA[0], qA[1], qA[2], qA[3]};
  __m256d b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_mul_pd(a, b);
  return UnpackDouble(result);
}

BQuad Sub(BQUADPAIR) {
  __m256i a{qA[0], qA[1], qA[2], qA[3]};
  __m256i b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_sub_epi16(a, b);
  return UnpackChar(result);
}

FQuad Sub(FQUADPAIR) {
  __m256 a{qA[0], qA[1], qA[2], qA[3]};
  __m256 b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_sub_ps(a, b);
  return UnpackFloat(result);
}

DQuad Sub(DQUADPAIR) {
  __m256d a{qA[0], qA[1], qA[2], qA[3]};
  __m256d b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_sub_pd(a, b);
  return UnpackDouble(result);
}

BQuad Div(BQUADPAIR) {
  __m256 a{static_cast<float>(qA[0]), static_cast<float>(qA[1]),
           static_cast<float>(qA[2]), static_cast<float>(qA[3])};
  __m256 b{static_cast<float>(qB[0]), static_cast<float>(qB[1]),
           static_cast<float>(qB[2]), static_cast<float>(qB[3])};
  auto result = _mm256_div_ps(a, b);
  return UnpackChar(result);
}

FQuad Div(FQUADPAIR) {
  __m256 a{qA[0], qA[1], qA[2], qA[3]};
  __m256 b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_div_ps(a, b);
  return UnpackFloat(result);
}

DQuad Div(DQUADPAIR) {
  __m256d a{qA[0], qA[1], qA[2], qA[3]};
  __m256d b{qB[0], qB[1], qB[2], qB[3]};
  auto result = _mm256_div_pd(a, b);
  return UnpackDouble(result);
}

} // namespace Pixel
} // namespace ag