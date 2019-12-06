#include "Pixel/Double.hpp"
#include "Math.hpp"

namespace Pixel {

// dRGB functions

dRGB::dRGB(double r, double g, double b) : _r{r}, _g{g}, _b{b} {}

dRGB::dRGB() : dRGB(0.0, 0.0, 0.0) {}

double dRGB::R() const { return _r; }

double &dRGB::R() { return _r; }

unsigned dRGB::uR() const { return static_cast<unsigned>(_r * 255.99); }

double dRGB::G() const { return _g; }

double &dRGB::G() { return _g; }

unsigned dRGB::uG() const { return static_cast<unsigned>(_g * 255.99); }

double dRGB::B() const { return _b; }

double &dRGB::B() { return _b; }

unsigned dRGB::uB() const { return static_cast<unsigned>(_b * 255.99); }

// dRGBA functions

dRGBA::dRGBA(double r, double g, double b, double a) : dRGB(r, g, b), _a{a} {}

dRGBA::dRGBA() : dRGBA(0.0, 0.0, 0.0, 0.0) {}

double dRGBA::A() const { return _a; }

double &dRGBA::A() { return _a; }

unsigned dRGBA::uA() const { return static_cast<unsigned>(_a * 255.99); }

// Operator overloads

void dRGB::operator+=(dRGB &other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
}

void dRGB::operator-=(dRGB &other) {
  _r -= other.R();
  _g -= other.G();
  _b -= other.B();
}

void dRGB::operator+=(double value) {
  _r += value;
  _g += value;
  _b += value;
}

void dRGB::operator-=(double value) { operator+=(-value); }

void dRGB::operator*=(double value) {
  _r *= value;
  _g *= value;
  _b *= value;
}

void dRGB::operator/=(double value) { operator*=(1.0f / value); }

void dRGBA::operator+=(dRGBA &other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
  _a += other.A();
}

void dRGBA::operator-=(dRGBA &other) {
  _r -= other.R();
  _g -= other.G();
  _b -= other.B();
  _a -= other.A();
}

void dRGBA::operator+=(double value) {
  dRGB::operator+=(value);
  _a += value;
}

void dRGBA::operator-=(double value) {
  dRGB::operator-=(value);
  _a -= value;
}

void dRGBA::operator*=(double value) {
  dRGB::operator*=(value);
  _a *= value;
}

void dRGBA::operator/=(double value) {
  double v = 1 / value;
  operator*=(v);
}

// Static operator overloads

PIXEL_API inline dRGB operator+(const dRGB &a, const dRGB &b) {
  auto x = Add(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGB operator-(const dRGB &a, const dRGB &b) {
  auto x = Sub(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGB operator*(const dRGB &a, const dRGB &b) {
  auto x = Mul(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGB operator/(const dRGB &a, const dRGB &b) {
  auto x = Div(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGB operator+(const dRGB &rgb, const double value) {
  auto x = Add(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGB operator-(const dRGB &rgb, const double value) {
  auto x = Sub(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGB operator*(const dRGB &rgb, const double value) {
  auto x = Mul(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGB operator/(const dRGB &rgb, const double value) {
  auto x = Div(rgb.R(), value, rgb.G(), value, rgb.B(), value, 0.0, 0.0);
  return {x[0], x[1], x[2]};
}

PIXEL_API inline dRGBA operator+(const dRGBA &a, const dRGBA &b) {
  auto x = Add(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline dRGBA operator-(const dRGBA &a, const dRGBA &b) {
  auto x = Sub(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline dRGBA operator*(const dRGBA &a, const dRGBA &b) {
  auto x = Mul(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline dRGBA operator/(const dRGBA &a, const dRGBA &b) {
  auto x = Div(a.R(), b.R(), a.G(), b.G(), a.B(), b.B(), a.A(), b.A());
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline dRGBA operator+(const dRGBA &rgba, const double value) {
  auto x =
      Add(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline dRGBA operator-(const dRGBA &rgba, const double value) {
  auto x =
      Sub(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline dRGBA operator*(const dRGBA &rgba, const double value) {
  auto x =
      Mul(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

PIXEL_API inline dRGBA operator/(const dRGBA &rgba, const double value) {
  auto x =
      Div(rgba.R(), value, rgba.G(), value, rgba.B(), value, rgba.A(), value);
  return {x[0], x[1], x[2], x[3]};
}

} // namespace Pixel