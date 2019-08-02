#pragma once

#include <cstdint>

namespace Pixel {

// Save some space
#define BYTE uint8_t

// Save lots of space
#define BYTEQUAD BYTE a1, BYTE a2, BYTE b1, BYTE b2, BYTE c1, BYTE c2, BYTE d1, BYTE d2
#define FLOATQUAD float a1, float a2, float b1, float b2, float c1, float c2, float d1, float d2
#define DOUBLEQUAD double a1, double a2, double b1, double b2, double c1, double c2, double d1, double d2

// Just a little something so I don't have to use pointer arrays
template <typename T>
struct Quad {
    T values[4];

    T &operator[] (const unsigned i) {
        return values[i];
    }

    T operator[] (const unsigned i) const {
        return values[i];
    }

    // Bit unsafe, but this only ever contains numeric types
    Quad() : Quad {0, 0, 0, 0} {
           
    }

    Quad(T a, T b, T c, T d) {
        values[0] = a;
        values[1] = b;
        values[2] = c;
        values[3] = d;
    }

    Quad (T *v) {
        values[0] = v[0];
        values[1] = v[1];
        values[2] = v[2];
        values[3] = v[3];
    }
};

// I don't like templating everything I use
using BQuad = Quad<BYTE>;
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

}