#include "Math/Math.hpp"

#include "Core.hpp"
#include "Math.hpp"

namespace ag {
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

BQuad Add(BYTEQUAD) { return Add<BYTE>(a1, a2, b1, b2, c1, c2, d1, d2); }

FQuad Add(FLOATQUAD) { return Add<float>(a1, a2, b1, b2, c1, c2, d1, d2); }

DQuad Add(DOUBLEQUAD) { return Add<double>(a1, a2, b1, b2, c1, c2, d1, d2); }

BQuad Mul(BYTEQUAD) { return Mul<BYTE>(a1, a2, b1, b2, c1, c2, d1, d2); }

FQuad Mul(FLOATQUAD) { return Mul<float>(a1, a2, b1, b2, c1, c2, d1, d2); }

DQuad Mul(DOUBLEQUAD) { return Mul<double>(a1, a2, b1, b2, c1, c2, d1, d2); }

BQuad Sub(BYTEQUAD) { return Sub<BYTE>(a1, a2, b1, b2, c1, c2, d1, d2); }

FQuad Sub(FLOATQUAD) { return Sub<float>(a1, a2, b1, b2, c1, c2, d1, d2); }

DQuad Sub(DOUBLEQUAD) { return Sub<double>(a1, a2, b1, b2, c1, c2, d1, d2); }

BQuad Div(BYTEQUAD) { return Div<BYTE>(a1, a2, b1, b2, c1, c2, d1, d2); }

FQuad Div(FLOATQUAD) { return Div<float>(a1, a2, b1, b2, c1, c2, d1, d2); }

DQuad Div(DOUBLEQUAD) { return Div<double>(a1, a2, b1, b2, c1, c2, d1, d2); }

BQuad Add(BQUADPAIR) {
  return Add<BYTE>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

FQuad Add(FQUADPAIR) {
  return Add<float>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

DQuad Add(DQUADPAIR) {
  return Add<double>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

BQuad Mul(BQUADPAIR) {
  return Mul<BYTE>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

FQuad Mul(FQUADPAIR) {
  return Mul<float>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

DQuad Mul(DQUADPAIR) {
  return Mul<double>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

BQuad Sub(BQUADPAIR) {
  return Sub<BYTE>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

FQuad Sub(FQUADPAIR) {
  return Sub<float>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

DQuad Sub(DQUADPAIR) {
  return Sub<double>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

BQuad Div(BQUADPAIR) {
  return Div<BYTE>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

FQuad Div(FQUADPAIR) {
  return Div<float>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

DQuad Div(DQUADPAIR) {
  return Div<double>(qA[0], qB[0], qA[1], qB[1], qA[2], qB[2], qA[3], qB[3]);
}

} // namespace Pixel
} // namespace ag