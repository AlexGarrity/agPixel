#include "Math/PixelPackedMath.hpp"

namespace Pixel {

    BQuad4 Add(BQuad4 a, BQuad4 b) {
        BQuad4 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] + b.a[i];
            out.b[i] = a.b[i] + b.b[i];
            out.c[i] = a.c[i] + b.c[i];
            out.d[i] = a.d[i] + b.d[i];
        }
        return out;
    }

    BQuad4 Mul(BQuad4 a, BQuad4 b) {
        BQuad4 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] * b.a[i];
            out.b[i] = a.b[i] * b.b[i];
            out.c[i] = a.c[i] * b.c[i];
            out.d[i] = a.d[i] * b.d[i];
        }
        return out;
    }

    BQuad4 Sub(BQuad4 a, BQuad4 b) {
        BQuad4 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] - b.a[i];
            out.b[i] = a.b[i] - b.b[i];
            out.c[i] = a.c[i] - b.c[i];
            out.d[i] = a.d[i] - b.d[i];
        }
        return out;
    }

    BQuad4 Div(BQuad4 a, BQuad4 b) {
        BQuad4 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] / b.a[i];
            out.b[i] = a.b[i] / b.b[i];
            out.c[i] = a.c[i] / b.c[i];
            out.d[i] = a.d[i] / b.d[i];
        }
        return out;
    }


    BQuad8 Add(BQuad8 a, BQuad8 b) {
        BQuad8 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] + b.a[i];
            out.b[i] = a.b[i] + b.b[i];
            out.c[i] = a.c[i] + b.c[i];
            out.d[i] = a.d[i] + b.d[i];
            out.e[i] = a.e[i] + b.e[i];
            out.f[i] = a.f[i] + b.f[i];
            out.g[i] = a.g[i] + b.g[i];
            out.h[i] = a.h[i] + b.h[i];
        }
        return out;
    }

    BQuad8 Mul(BQuad8 a, BQuad8 b) {
        BQuad8 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] * b.a[i];
            out.b[i] = a.b[i] * b.b[i];
            out.c[i] = a.c[i] * b.c[i];
            out.d[i] = a.d[i] * b.d[i];
            out.e[i] = a.e[i] * b.e[i];
            out.f[i] = a.f[i] * b.f[i];
            out.g[i] = a.g[i] * b.g[i];
            out.h[i] = a.h[i] * b.h[i];
        }
        return out;
    }

    BQuad8 Sub(BQuad8 a, BQuad8 b) {
        BQuad8 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] - b.a[i];
            out.b[i] = a.b[i] - b.b[i];
            out.c[i] = a.c[i] - b.c[i];
            out.d[i] = a.d[i] - b.d[i];
            out.e[i] = a.e[i] - b.e[i];
            out.f[i] = a.f[i] - b.f[i];
            out.g[i] = a.g[i] - b.g[i];
            out.h[i] = a.h[i] - b.h[i];
        }
        return out;
    }

    BQuad8 Div(BQuad8 a, BQuad8 b) {
        BQuad8 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] / b.a[i];
            out.b[i] = a.b[i] / b.b[i];
            out.c[i] = a.c[i] / b.c[i];
            out.d[i] = a.d[i] / b.d[i];
            out.e[i] = a.e[i] / b.e[i];
            out.f[i] = a.f[i] / b.f[i];
            out.g[i] = a.g[i] / b.g[i];
            out.h[i] = a.h[i] / b.h[i];
        }
        return out;
    }

    FQuad2 Add(FQuad2 a, FQuad2 b) {
        FQuad2 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] + b.a[i];
            out.b[i] = a.b[i] + b.b[i];
        }
        return out;
    }

    FQuad2 Mul(FQuad2 a, FQuad2 b) {
        FQuad2 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] * b.a[i];
            out.b[i] = a.b[i] * b.b[i];
        }
        return out;
    }

    FQuad2 Sub(FQuad2 a, FQuad2 b) {
        FQuad2 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] - b.a[i];
            out.b[i] = a.b[i] - b.b[i];
        }
        return out;
    }

    FQuad2 Div(FQuad2 a, FQuad2 b) {
        FQuad2 out;
        for (unsigned i = 0; i < 3; ++i) {
            out.a[i] = a.a[i] / b.a[i];
            out.b[i] = a.b[i] / b.b[i];
        }
        return out;
    }

}