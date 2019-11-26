#include "Math/PixelMath.hpp"

namespace Pixel {

// No extensions so we'll use regular functions...

// Some templated helpers to save space
template <typename T>
Quad<T> Add(T a1, T a2, T b1, T b2, T c1, T c2, T d1, T d2) {
  Quad<T> out;
  out[0] = a1 + a1;
  out[1] = b1 + b2;
  out[2] = c1 + c2;
  out[3] = d1 + d2;
  return out;
}

template <typename T>
Quad<T> Mul(T a1, T a2, T b1, T b2, T c1, T c2, T d1, T d2) {
  Quad<T> out;
  out[0] = a1 * a1;
  out[1] = b1 * b2;
  out[2] = c1 * c2;
  out[3] = d1 * d2;
  return out;
}

template <typename T>
Quad<T> Sub(T a1, T a2, T b1, T b2, T c1, T c2, T d1, T d2) {
  Quad<T> out;
  out[0] = a1 - a1;
  out[1] = b1 - b2;
  out[2] = c1 - c2;
  out[3] = d1 - d2;
  return out;
}

template <typename T>
Quad<T> Div(T a1, T a2, T b1, T b2, T c1, T c2, T d1, T d2) {
  Quad<T> out;
  out[0] = a1 / a1;
  out[1] = b1 / b2;
  out[2] = c1 / c2;
  out[3] = d1 / d2;
  return out;
}


BQuad Add(BYTEQUAD) {
  return Add<BYTE>(a1, a2, b1, b2, c1, c2, d1,  d2);
}

FQuad Add(FLOATQUAD) {
  return Add<float>(a1, a2, b1, b2, c1, c2, d1, d2);
}

DQuad Add(DOUBLEQUAD) {
  return Add<double>(a1, a2, b1, b2, c1, c2, d1, d2);
}


BQuad Mul(BYTEQUAD) {
  return Mul<BYTE>(a1, a2, b1, b2, c1, c2, d1, d2);
}

FQuad Mul(FLOATQUAD) {
  return Mul<float>(a1, a2, b1, b2, c1, c2, d1, d2);
}

DQuad Mul(DOUBLEQUAD) {
  return Mul<double>(a1, a2, b1, b2, c1, c2, d1, d2);
}


BQuad Sub(BYTEQUAD) {
  return Sub<BYTE>(a1, a2, b1, b2, c1, c2, d1, d2);
}

FQuad Sub(FLOATQUAD) {
  return Sub<float>(a1, a2, b1, b2, c1, c2, d1, d2);
}

DQuad Sub(DOUBLEQUAD) {
  return Sub<double>(a1, a2, b1, b2, c1, c2, d1, d2);
}


BQuad Div(BYTEQUAD) {
  return Div<BYTE>(a1, a2, b1, b2, c1, c2, d1, d2);
}

FQuad Div(FLOATQUAD) {
  return Div<float>(a1, a2, b1, b2, c1, c2, d1, d2);
}

DQuad Div(DOUBLEQUAD) {
  return Div<double>(a1, a2, b1, b2, c1, c2, d1, d2);
}

}