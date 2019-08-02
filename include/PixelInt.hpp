#pragma once

#include "PixelCore.hpp"
#include <cstdint>

// Traditional integer representations of pixels
// Designed to be highly efficient and use as little space as possible
// Also very cheap to work with

namespace Pixel {

// RGB is the simplest way to represent a pixel, using only red, green, and blue
class PIXEL_API RGB {
protected:
    uint8_t _r;
    uint8_t _g;
    uint8_t _b;

public:
    explicit RGB(const uint8_t* rgb);
    RGB(uint8_t r, uint8_t g, uint8_t b);
    RGB();

    uint8_t R() const;
    uint8_t& R();

    uint8_t G() const;
    uint8_t& G();

    uint8_t B() const;
    uint8_t& B();

public:
    void operator+=(const RGB& other);
    void operator-=(const RGB& other);

    virtual void operator+=(uint8_t value);
    virtual void operator-=(uint8_t value);
    virtual void operator*=(uint8_t value);
    virtual void operator/=(uint8_t value);
};

// RGBA is an extension of RGB, adding support for alpha
class PIXEL_API RGBA : public RGB {
protected:
    uint8_t _a;

public:
    RGBA(const uint8_t *rgba);
    RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    RGBA();

    uint8_t A() const;
    uint8_t& A();

public:
    void operator+=(const RGBA& other);
    void operator-=(const RGBA& other);
    void operator+=(uint8_t value) override;
    void operator-=(uint8_t value) override;
    void operator*=(uint8_t value) override;
    void operator/=(uint8_t value) override;
};

}; // namespace Pixel