#include "PixelFloat.h"


namespace Pixel {
    
    // fRGB functions

    fRGB::fRGB(float r, float g, float b) : _r{r}, _g{g}, _b{b}
    {

    }

    fRGB::fRGB() : fRGB(0.0, 0.0, 0.0)
    {
        
    }

    float fRGB::R() const { 
        return _r;
    }

    float &fRGB::R() {
        return _r;
    }

    unsigned fRGB::uR() const {
        return static_cast<unsigned> (_r * 255.99);
    }

    float fRGB::G() const { 
        return _g;
    }

    float &fRGB::G() {
        return _g;
    }

    unsigned fRGB::uG() const {
        return static_cast<unsigned> (_g * 255.99);
    }

    float fRGB::B() const { 
        return _b;
    }

    float &fRGB::B() {
        return _b;
    }

    unsigned fRGB::uB() const {
        return static_cast<unsigned> (_b * 255.99);
    }



    // fRGBA functions

    fRGBA::fRGBA(float r, float g, float b, float a) : fRGB(r, g, b), _a{a}
    {

    }

    fRGBA::fRGBA() : fRGBA(0.0, 0.0, 0.0, 0.0)
    {

    }

    float fRGBA::A() const { 
        return _a;
    }

    float &fRGBA::A() {
        return _a;
    }

    unsigned fRGBA::uA() const {
        return static_cast<float> (_a * 255.99);
    }

}