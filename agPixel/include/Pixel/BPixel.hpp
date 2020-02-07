#pragma once

#include "Pixel.hpp"

namespace ag {
namespace Pixel {

class bRGBA : public PixelRGBA<uint8_t> {
    public:
        bRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : PixelRGBA<uint8_t> (r,g,b,a) {}
        bRGBA(uint8_t v)
        : PixelRGBA<uint8_t> (v) {}
        bRGBA()
        : PixelRGBA<uint8_t> (0) {}

        uint8_t R() const;
        uint8_t &R();
        uint8_t G() const;
        uint8_t &G();
        uint8_t B() const;
        uint8_t &B();
        uint8_t A() const;
        uint8_t &A();

        float fR() const;
        float fG() const;
        float fB() const;
        float fA() const;

        void operator+=(bRGBA &other);
        void operator-=(bRGBA &other);
        void operator*=(bRGBA &other);
        void operator/=(bRGBA &other);
    
        void operator+=(uint8_t v);
        void operator-=(uint8_t v);
        void operator*=(uint8_t v);
        void operator/=(uint8_t v);
};

};
};