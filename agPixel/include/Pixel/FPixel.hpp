#pragma once

#include "Pixel.hpp"

namespace ag {
namespace Pixel {

class AG_API fRGBA : public PixelRGBA<float> {
    public:
        fRGBA(float r, float g, float b, float a)
        : PixelRGBA<float> (r,g,b,a) {}
        fRGBA(float v)
        : PixelRGBA<float> (v) {}
        fRGBA()
        : PixelRGBA<float> (0) {}

        float R() const;
        float &R();
        float G() const;
        float &G();
        float B() const;
        float &B();
        float A() const;
        float &A();

        uint8_t uR() const;
        uint8_t uG() const;
        uint8_t uB() const;
        uint8_t uA() const;

        void operator+=(fRGBA &other);
        void operator-=(fRGBA &other);
        void operator*=(fRGBA &other);
        void operator/=(fRGBA &other);
    
        void operator+=(float v);
        void operator-=(float v);
        void operator*=(float v);
        void operator/=(float v);
};

};
};