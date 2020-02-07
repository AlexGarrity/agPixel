#pragma once

#include "Pixel.hpp"

namespace ag {
namespace Pixel {

class AG_API dRGBA : public PixelRGBA<double> {
    public:
        dRGBA(double r, double g, double b, double a)
        : PixelRGBA<double> (r,g,b,a) {}
        dRGBA(double v)
        : PixelRGBA<double> (v) {}
        dRGBA()
        : PixelRGBA<double> (0) {}

        double R() const;
        double &R();
        double G() const;
        double &G();
        double B() const;
        double &B();
        double A() const;
        double &A();

        uint8_t uR() const;
        uint8_t uG() const;
        uint8_t uB() const;
        uint8_t uA() const;

        void operator+=(dRGBA &other);
        void operator-=(dRGBA &other);
        void operator*=(dRGBA &other);
        void operator/=(dRGBA &other);
    
        void operator+=(double v);
        void operator-=(double v);
        void operator*=(double v);
        void operator/=(double v);
};

};
};