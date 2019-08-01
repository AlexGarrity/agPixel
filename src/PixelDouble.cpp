#include "PixelDouble.hpp"

namespace Pixel {

// dRGB functions

dRGB::dRGB(double r, double g, double b) : _r{r}, _g{g}, _b{b} {}

dRGB::dRGB() : dRGB(0.0, 0.0, 0.0) {}

double dRGB::R() const {
  return _r;
}

double& dRGB::R() {
  return _r;
}

unsigned dRGB::uR() const {
  return static_cast<unsigned>(_r * 255.99);
}

double dRGB::G() const {
  return _g;
}

double& dRGB::G() {
  return _g;
}

unsigned dRGB::uG() const {
  return static_cast<unsigned>(_g * 255.99);
}

double dRGB::B() const {
  return _b;
}

double& dRGB::B() {
  return _b;
}

unsigned dRGB::uB() const {
  return static_cast<unsigned>(_b * 255.99);
}

// dRGBA functions

dRGBA::dRGBA(double r, double g, double b, double a) : dRGB(r, g, b), _a{a} {}

dRGBA::dRGBA() : dRGBA(0.0, 0.0, 0.0, 0.0) {}

double dRGBA::A() const {
  return _a;
}

double& dRGBA::A() {
  return _a;
}

unsigned dRGBA::uA() const {
  return static_cast<unsigned>(_a * 255.99);
}

// Operator overloads

void dRGB::operator+=(dRGB& other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
}

void dRGB::operator-=(dRGB& other) {
  _r -= other.R();
  _g -= other.G();
  _b -= other.B();
}

void dRGB::operator+=(double value) {
  _r += value;
  _g += value;
  _b += value;
}

void dRGB::operator-=(double value) {
  operator+=(-value);
}

void dRGB::operator*=(double value) {
  _r *= value;
  _g *= value;
  _b *= value;
}

void dRGB::operator/=(double value) {
  operator*=(1.0f / value);
}

void dRGBA::operator+=(dRGBA& other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
  _a += other.A();
}

void dRGBA::operator-=(dRGBA& other) {
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

PIXEL_API inline dRGB operator+(const dRGB& a, const dRGB& b) {
  return {a.R() + b.R(), a.G() + b.G(), a.B() + b.B()};
}

PIXEL_API inline dRGB operator-(const dRGB& a, const dRGB& b) {
  return {a.R() - b.R(), a.G() - b.G(), a.B() - b.B()};
}

PIXEL_API inline dRGB operator*(const dRGB& a, const dRGB& b) {
  return {a.R() * b.R(), a.G() * b.G(), a.B() * b.B()};
}

PIXEL_API inline dRGB operator/(const dRGB& a, const dRGB& b) {
  return {a.R() / b.R(), a.G() / b.G(), a.B() / b.B()};
}

PIXEL_API inline dRGB operator+(const dRGB& rgb, const double value) {
  return {rgb.R() + value, rgb.G() + value, rgb.B() + value};
}

PIXEL_API inline dRGB operator-(const dRGB& rgb, const double value) {
  return {rgb.R() - value, rgb.G() - value, rgb.B() - value};
}

PIXEL_API inline dRGB operator*(const dRGB& rgb, const double value) {
  return {rgb.R() * value, rgb.G() * value, rgb.B() * value};
}

PIXEL_API inline dRGB operator/(const dRGB& rgb, const double value) {
  return {rgb.R() / value, rgb.G() / value, rgb.B() / value};
}

PIXEL_API inline dRGBA operator+(const dRGBA& a, const dRGBA& b) {
  return {a.R() + b.R(), a.G() + b.G(), a.B() + b.B(), a.A() + b.A()};
}

PIXEL_API inline dRGBA operator-(const dRGBA& a, const dRGBA& b) {
  return {a.R() - b.R(), a.G() - b.G(), a.B() - b.B(), a.A() - b.A()};
}

PIXEL_API inline dRGBA operator*(const dRGBA& a, const dRGBA& b) {
  return {a.R() * b.R(), a.G() * b.G(), a.B() * b.B(), a.A() * b.A()};
}

PIXEL_API inline dRGBA operator/(const dRGBA& a, const dRGBA& b) {
  return {a.R() / b.R(), a.G() / b.G(), a.B() / b.B(), a.A() / b.A()};
}

PIXEL_API inline dRGBA operator+(const dRGBA& rgba, const double value) {
  return {rgba.R() + value, rgba.G() + value, rgba.B() + value,
          rgba.A() + value};
}

PIXEL_API inline dRGBA operator-(const dRGBA& rgba, const double value) {
  return {rgba.R() - value, rgba.G() - value, rgba.B() - value,
          rgba.A() - value};
}

PIXEL_API inline dRGBA operator*(const dRGBA& rgba, const double value) {
  return {rgba.R() * value, rgba.G() * value, rgba.B() * value,
          rgba.A() * value};
}

PIXEL_API inline dRGBA operator/(const dRGBA& rgba, const double value) {
  return {rgba.R() / value, rgba.G() / value, rgba.B() / value,
          rgba.A() / value};
}

}  // namespace Pixel