#include "Pixel/Int.hpp"
#include "Math.hpp"

namespace ag {
namespace Pixel {

// RGB functions

RGB::RGB(const uint8_t *rgb) : _r{rgb[0]}, _g{rgb[1]}, _b{rgb[2]} {
  delete[] rgb;
}

RGB::RGB(const uint8_t r, const uint8_t g, const uint8_t b)
    : _r{r}, _g{g}, _b{b} {}

RGB::RGB() : RGB(0, 0, 0) {}

uint8_t RGB::R() const { return _r; }

uint8_t &RGB::R() { return _r; }

uint8_t RGB::G() const { return _g; }

uint8_t &RGB::G() { return _g; }

uint8_t RGB::B() const { return _b; }

uint8_t &RGB::B() { return _b; }

// RGBA functions

RGBA::RGBA(const uint8_t *rgba) : RGB(rgba[0], rgba[1], rgba[2]), _a{rgba[3]} {
  delete[] rgba;
}

RGBA::RGBA(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    : RGB(r, g, b), _a{a} {}

RGBA::RGBA() : RGBA(0, 0, 0, 0) {}

uint8_t RGBA::A() const { return _a; }

uint8_t &RGBA::A() { return _a; }

// Operator overloads

void RGB::operator+=(const uint8_t value) {
  _r += value;
  _g += value;
  _b += value;
}

void RGB::operator-=(const uint8_t value) {
  _r -= value;
  _g -= value;
  _b -= value;
}

void RGB::operator*=(const uint8_t value) {
  _r *= value;
  _g *= value;
  _b *= value;
}

void RGB::operator/=(const uint8_t value) {
  _r /= value;
  _g /= value;
  _b /= value;
}

void RGB::operator+=(const RGB &other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
}

void RGB::operator-=(const RGB &other) {
  _r -= other.R();
  _g -= other.G();
  _b -= other.B();
}

void RGBA::operator+=(const uint8_t value) {
  RGB::operator+=(value);
  _a += value;
}

void RGBA::operator-=(const uint8_t value) {
  RGB::operator-=(value);
  _a -= value;
}

void RGBA::operator*=(const uint8_t value) {
  RGB::operator*=(value);
  _a *= value;
}

void RGBA::operator/=(const uint8_t value) {
  RGB::operator/=(value);
  _a /= value;
}

void RGBA::operator+=(const RGBA &other) {
  RGB::operator+=(other);
  _a += other.A();
}

void RGBA::operator-=(const RGBA &other) {
  RGB::operator-=(other);
  _a -= other.A();
}

// Static operator overloads

PIXEL_API inline RGB operator+(const RGB &a, const RGB &b) {
  auto x = Add(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGB operator-(const RGB &a, const RGB &b) {
  auto x = Sub(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGB operator*(const RGB &a, const RGB &b) {
  auto x = Mul(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGB operator/(const RGB &a, const RGB &b) {
  auto x = Div(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGB operator+(const RGB &rgb, const uint8_t value) {
  auto x = Add(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGB operator-(const RGB &rgb, const uint8_t value) {
  auto x = Sub(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGB operator*(const RGB &rgb, const uint8_t value) {
  auto x = Mul(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGB operator/(const RGB &rgb, const uint8_t value) {
  auto x = Div(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0, 0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline RGBA operator+(const RGBA &a, const RGBA &b) {
  auto x = Add(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline RGBA operator-(const RGBA &a, const RGBA &b) {
  auto x = Sub(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline RGBA operator*(const RGBA &a, const RGBA &b) {
  auto x = Mul(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline RGBA operator/(const RGBA &a, const RGBA &b) {
  auto x = Div(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline RGBA operator+(const RGBA &rgba, const uint8_t value) {
  auto x =
      Add(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline RGBA operator-(const RGBA &rgba, const uint8_t value) {
  auto x =
      Sub(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline RGBA operator*(const RGBA &rgba, const uint8_t value) {
  auto x =
      Mul(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline RGBA operator/(const RGBA &rgba, const uint8_t value) {
  auto x =
      Div(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

} // namespace Pixel
}