#pragma once

// Traditional integer representations of piexls
// Designed to be highly efficient and use as little space as possible
// Also very cheap to work with

namespace Pixel {

    // RGB is the simplest way to represent a pixel, using only red, green, and blue
    class RGB {
        protected:
            char _r;
            char _g;
            char _b;

        public:
            RGB(char  r, char  g, char  b);
            RGB();

            char R() const;
            char &R();

            char G() const;
            char &G();

            char B() const;
            char &B();

    };

    // RGBA is an extension of RGB, adding support for alpha
    class RGBA : public RGB {
        protected:
            char _a;

        public:
            RGBA(char r, char g, char b, char a);
            RGBA();

            char A() const;
            char &A();
    };

};