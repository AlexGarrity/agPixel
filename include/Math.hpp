#pragma once

// PixelMath automatically chooses the right version of the header dependent of
// whether or not you enabled extensions It otherwise does nothing

#include <cstdint>

#include "Core.hpp"

namespace ag {
namespace Pixel {

// Save some space
#define BYTE uint8_t
#define WORD uint32_t
#define DWORD uint64_t

// Save lots of space
#define BYTEQUAD                                                               \
  const BYTE a1, const BYTE a2, const BYTE b1, const BYTE b2, const BYTE c1,   \
      const BYTE c2, const BYTE d1, const BYTE d2
#define FLOATQUAD                                                              \
  const float a1, const float a2, const float b1, const float b2,              \
      const float c1, const float c2, const float d1, const float d2
#define DOUBLEQUAD                                                             \
  const double a1, const double a2, const double b1, const double b2,          \
      const double c1, const double c2, const double d1, const double d2


// Save lots more space
#define BQUADPAIR                                                             \
  const BQuad qA, const BQuad qB
#define FQUADPAIR                                                             \
  const FQuad qA, const FQuad qB
#define DQUADPAIR                                                             \
  const DQuad qA, const DQuad qB



// Just a little something so I don't have to use pointer arrays
template <typename T> struct Quad {
  T values[4];

  T &operator[](const unsigned i) { return values[i]; }

  T operator[](const unsigned i) const { return values[i]; }

  // Bit unsafe, but this only ever contains numeric types
  Quad() : Quad{0, 0, 0, 0} {}

  Quad(T a, T b, T c, T d) {
    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;
  }

  Quad(T *v) {
    values[0] = v[0];
    values[1] = v[1];
    values[2] = v[2];
    values[3] = v[3];
  }

  Quad(const T v) {
    values[0] = v;
    values[1] = v;
    values[2] = v;
    values[3] = v;
  }

};

// I don't like templating everything I use
using BQuad = Quad<BYTE>;
using SQuad = Quad<int16_t>;
using FQuad = Quad<float>;
using DQuad = Quad<double>;


// Declarations of maths functions
DQuad Add(DOUBLEQUAD);
FQuad Add(FLOATQUAD);
BQuad Add(BYTEQUAD);

DQuad Mul(DOUBLEQUAD);
FQuad Mul(FLOATQUAD);
BQuad Mul(BYTEQUAD);

DQuad Sub(DOUBLEQUAD);
FQuad Sub(FLOATQUAD);
BQuad Sub(BYTEQUAD);

DQuad Div(DOUBLEQUAD);
FQuad Div(FLOATQUAD);
BQuad Div(BYTEQUAD);


DQuad Add(DQUADPAIR);
FQuad Add(FQUADPAIR);
BQuad Add(BQUADPAIR);

DQuad Mul(DQUADPAIR);
FQuad Mul(FQUADPAIR);
BQuad Mul(BQUADPAIR);

DQuad Sub(DQUADPAIR);
FQuad Sub(FQUADPAIR);
BQuad Sub(BQUADPAIR);

DQuad Div(DQUADPAIR);
FQuad Div(FQUADPAIR);
BQuad Div(BQUADPAIR);

} // namespace Pixel
}