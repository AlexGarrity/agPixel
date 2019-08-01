#include "PixelMath.hpp"
#include "PixelCore.hpp"

// Caution:  This file has a really inconsistent code style
// Everything else is Chromium / Webkit, this is maybe LLVM?

#if defined(ENABLE_EXTENSIONS)
// Extensions are enabled, so use AVX2 rather than regular maths

// Some handy little helper functions for unpacking __mm256 types
char* UnpackChar(__m256i chars) {
  auto out = new char[4];
  out[0] = chars[0];
  out[1] = chars[1];
  out[2] = chars[2];
  out[3] = chars[3];
  return out;
}

float* UnpackFloat(__m256 floats) {
  auto out = new float[4];
  out[0] = floats[0];
  out[1] = floats[1];
  out[2] = floats[2];
  out[3] = floats[3];
  return out;
}

double* UnpackDouble(__m256d doubles) {
  auto out = new double[4];
  out[0] = doubles[0];
  out[1] = doubles[1];
  out[2] = doubles[2];
  out[3] = doubles[3];
  return out;
}


char *Add(char a1, char a2, char b1, char b2, char c1, char c2, char d1, char d2) {
  // Pack the chars into an __m256i...
  __m256i a{a1, b1, c1, d1};
  __m256i b{a2, b2, c2, d2};
  auto result = _mm256_add_epi8(a, b);
  // Unpack and return
  return UnpackChar(result);
}

float *Add(float a1, float a2, float b1, float b2, float c1, float c2, float d1, float d2) {
  __m256 a{a1, b1, c1, d1};
  __m256 b{a2, b2, c2, d2};
  auto result = _mm256_add_ps(a, b);
  return UnpackFloat(result);
}

double *Add(double a1, double a2, double b1, double b2, double c1, double c2, double d1, double d2) {
  __m256d a{a1, b1, c1, d1};
  __m256d b{a2, b2, c2, d2};
  auto result = _mm256_add_pd(a, b);
  return UnpackDouble(result);
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

float *Add(float a1, float a2, float b1, float b2, float c1, float c2, float d1, float d2) {
  float *out = new float[4];
  out[0] = a1 + a1;
  out[1] = b1 + b2;
  out[2] = c1 + c2;
  out[3] = d1 + d2;
  return out;
}

double *Add(double a1, double a2, double b1, double b2, double c1, double c2, double d1, double d2) {
  double *out = new double[4];
  out[0] = a1 + a1;
  out[1] = b1 + b2;
  out[2] = c1 + c2;
  out[3] = d1 + d2;
  return out;
}

#endif