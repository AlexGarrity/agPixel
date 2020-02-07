#pragma once

#include <agSIMD/Quad.hpp>
#include <agSIMD/Math.hpp>

namespace ag {
namespace Pixel {

using SIMD::Quad;

template<typename T>
class PixelRGBA : public Quad<T> {
    public:
        PixelRGBA(T r, T g, T b, T a) : Quad<T>(r, g, b, a) {}
        PixelRGBA(T v) : Quad<T>(v) {}
        PixelRGBA() : Quad<T>(0) {}
};

};
};