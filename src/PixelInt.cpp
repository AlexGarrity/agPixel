#include "PixelInt.h"

namespace Pixel {

    // RGB functions

    RGB::RGB(char r, char g, char b) : _r{r}, _g{g}, _b{b}
    {

    }

    RGB::RGB() : RGB(0, 0, 0)
    {

    }

    char RGB::R() const {
        return _r;
    }

    char &RGB::R() {
        return _r;
    }

    char RGB::G() const {
        return _g;
    }

    char &RGB::G() {
        return _g;
    }

    char RGB::B() const {
        return _b;
    }

    char &RGB::B() {
        return _b;
    }



    // RGBA functions

    RGBA::RGBA(char r, char g, char b, char a) : RGB(r, g, b), _a{a}
    {

    }

    RGBA::RGBA() : RGBA(0, 0, 0, 0) 
    {

    }

    char RGBA::A() const {
        return _a;
    }

    char &RGBA::A() {
        return _a;
    }
}