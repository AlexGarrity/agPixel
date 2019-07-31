#include "PixelInt.hpp"

namespace Pixel {

// RGB functions

RGB::RGB(const char r, const char g, const char b) : _r{r}, _g{g}, _b{b} {}

RGB::RGB() : RGB(0, 0, 0) {}

char RGB::R() const { return _r; }

char& RGB::R() { return _r; }

char RGB::G() const { return _g; }

char& RGB::G() { return _g; }

char RGB::B() const { return _b; }

char& RGB::B() { return _b; }

// RGBA functions

RGBA::RGBA(const char r, const char g, const char b, const char a)
    : RGB(r, g, b), _a{a} {}

RGBA::RGBA() : RGBA(0, 0, 0, 0) {}

char RGBA::A() const { return _a; }

char& RGBA::A() { return _a; }

// Operator overloads

void RGB::operator+=(const char value) {
  _r += value;
  _g += value;
  _b += value;
}

void RGB::operator-=(const char value) {
  _r -= value;
  _g -= value;
  _b -= value;
}

void RGB::operator*=(const char value) {
  _r *= value;
  _g *= value;
  _b *= value;
}

void RGB::operator/=(const char value) {
  _r /= value;
  _g /= value;
  _b /= value;
}

void RGB::operator+=(const RGB& other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
}

void RGB::operator-=(const RGB& other) {
  _r -= other.R();
  _g -= other.G();
  _b -= other.B();
}

void RGBA::operator+=(const char value) {
  RGB::operator+=(value);
  _a += value;
}

void RGBA::operator-=(const char value) {
  RGB::operator-=(value);
  _a -= value;
}

void RGBA::operator*=(const char value) {
  RGB::operator*=(value);
  _a *= value;
}

void RGBA::operator/=(const char value) {
  RGB::operator/=(value);
  _a /= value;
}

void RGBA::operator+=(const RGBA& other) {
  RGB::operator+=(other);
  _a += other.A();
}

void RGBA::operator-=(const RGBA& other) {
  RGB::operator-=(other);
  _a -= other.A();
}

// Static operator overloads

PIXEL_API inline RGB operator+(const RGB& a, const RGB& b) {
  return RGB(a.R() + b.R(), a.G() + b.G(), a.B() + b.B());
}

PIXEL_API inline RGB operator-(const RGB& a, const RGB& b) {
  return RGB(a.R() - b.R(), a.G() - b.G(), a.B() - b.B());
}

PIXEL_API inline RGB operator*(const RGB& a, const RGB& b) {
  return RGB(a.R() * b.R(), a.G() * b.G(), a.B() * b.B());
}

PIXEL_API inline RGB operator/(const RGB& a, const RGB& b) {
  return RGB(a.R() / b.R(), a.G() / b.G(), a.B() / b.B());
}

PIXEL_API inline RGB operator+(const RGB& rgb, const char value) {
  return RGB(rgb.R() + value, rgb.G() + value, rgb.B() + value);
}

PIXEL_API inline RGB operator-(const RGB& rgb, const char value) {
  return RGB(rgb.R() - value, rgb.G() - value, rgb.B() - value);
}

PIXEL_API inline RGB operator*(const RGB& rgb, const char value) {
  return RGB(rgb.R() * value, rgb.G() * value, rgb.B() * value);
}

PIXEL_API inline RGB operator/(const RGB& rgb, const char value) {
  return RGB(rgb.R() / value, rgb.G() / value, rgb.B() / value);
}

PIXEL_API inline RGBA operator+(const RGBA& a, const RGBA& b) {
  return RGBA(a.R() + b.R(), a.G() + b.G(), a.B() + b.B(), a.A() + b.A());
}

PIXEL_API inline RGBA operator-(const RGBA& a, const RGBA& b) {
  return RGBA(a.R() - b.R(), a.G() - b.G(), a.B() - b.B(), a.A() - b.A());
}

PIXEL_API inline RGBA operator*(const RGBA& a, const RGBA& b) {
  return RGBA(a.R() * b.R(), a.G() * b.G(), a.B() * b.B(), a.A() * b.A());
}

PIXEL_API inline RGBA operator/(const RGBA& a, const RGBA& b) {
  return RGBA(a.R() / b.R(), a.G() / b.G(), a.B() / b.B(), a.A() / b.A());
}

PIXEL_API inline RGBA operator+(const RGBA& rgba, const char value) {
  return RGBA(rgba.R() + value, rgba.G() + value, rgba.B() + value,
              rgba.A() + value);
}

PIXEL_API inline RGBA operator-(const RGBA& rgba, const char value) {
  return RGBA(rgba.R() - value, rgba.G() - value, rgba.B() - value,
              rgba.A() - value);
}

PIXEL_API inline RGBA operator*(const RGBA& rgba, const char value) {
  return RGBA(rgba.R() * value, rgba.G() * value, rgba.B() * value,
              rgba.A() * value);
}

PIXEL_API inline RGBA operator/(const RGBA& rgba, const char value) {
  return RGBA(rgba.R() / value, rgba.G() / value, rgba.B() / value,
              rgba.A() / value);
}

}  // namespace Pixel