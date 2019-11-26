#pragma once

#include "PixelCore.hpp"
#include "PixelMath.hpp"

namespace Pixel {

    // Only used for packing and unpacking
    // Saves me using pointers
    struct BQuad2 {
        BQuad a, b;
    };

    // BQuad4 contains four BQuads, thereby containing 16 bytes or 4 RGBA pixels
    // This fills half of an __m256i
    struct BQuad4 {
        BQuad a, b, c, d;
    };

    // BQuad8 contains eight BQuads, thereby containing 16 bytes or 8 RGBA pixels
    // This fills an __m256i
    struct BQuad8 {
        BQuad a, b, c, d, e, f, g, h;
    };

    struct FPair {
        float a, b;
    }

    // FQuad2 contains two FQuads, thereby containing 8 floats or 2 fRGBA pixels
    // This fills __m256
    struct FQuad2 {
        FQuad a, b;
    };


    BQuad4 Add(BQuad4 a, BQuad4 b);
    BQuad4 Mul(BQuad4 a, BQuad4 b);
    BQuad4 Sub(BQuad4 a, BQuad4 b);
    BQuad4 Div(BQuad4 a, BQuad4 b);

    BQuad8 Add(BQuad8 a, BQuad8 b);
    BQuad8 Mul(BQuad8 a, BQuad8 b);
    BQuad8 Sub(BQuad8 a, BQuad8 b);
    BQuad8 Div(BQuad8 a, BQuad8 b);

    FQuad2 Add(FQuad2 a, FQuad2 b);
    FQuad2 Mul(FQuad2 a, FQuad2 b);
    FQuad2 Sub(FQuad2 a, FQuad2 b);
    FQuad2 Div(FQuad2 a, FQuad2 b);

}