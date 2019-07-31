#pragma once

// Double representations of pixels
// Even more CPU intensive to use, but also even more accurate
// Suited for applications such as really accurate ray tracing

#include "PixelCore.hpp"

namespace Pixel {

// dRGB is the simplest way to represent a pixel, using only red, green, and
// blue
    class PIXEL_API dRGB {
    protected:
        double _r;
        double _g;
        double _b;

    public:
        dRGB(double r, double g, double b);
        dRGB();

        double R() const;
        double& R();
        unsigned uR() const;

        double G() const;
        double& G();
        unsigned uG() const;

        double B() const;
        double& B();
        unsigned uB() const;

    public:
        void operator+=(dRGB& other);
        void operator-=(dRGB& other);

        virtual void operator+=(double value);

        virtual void operator-=(double value);

        virtual void operator*=(double value);

        virtual void operator/=(double value);
    };

// dRGBA is an extension of dRGB, adding support for alpha
    class PIXEL_API dRGBA : public dRGB {
    protected:
        double _a;

    public:
        dRGBA(double r, double g, double b, double a);
        dRGBA();

        double A() const;
        double& A();
        unsigned uA() const;

    public:
        void operator+=(dRGBA& other);
        void operator-=(dRGBA& other);
        void operator+=(double value) override;
        void operator-=(double value) override;
        void operator*=(double value) override;
        void operator/=(double value) override;
    };

};  // namespace Pixel