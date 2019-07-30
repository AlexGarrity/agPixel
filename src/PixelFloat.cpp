#include "PixelFloat.hpp"

namespace Pixel {

// fRGB functions

fRGB::fRGB(float r, float g, float b) : _r{r}, _g{g}, _b{b} {}

fRGB::fRGB() : fRGB(0.0, 0.0, 0.0) {}

float fRGB::R() const { return _r; }

float& fRGB::R() { return _r; }

unsigned fRGB::uR() const { return static_cast<unsigned>(_r * 255.99); }

float fRGB::G() const { return _g; }

float& fRGB::G() { return _g; }

unsigned fRGB::uG() const { return static_cast<unsigned>(_g * 255.99); }

float fRGB::B() const { return _b; }

float& fRGB::B() { return _b; }

unsigned fRGB::uB() const { return static_cast<unsigned>(_b * 255.99); }

// fRGBA functions

fRGBA::fRGBA(float r, float g, float b, float a) : fRGB(r, g, b), _a{a} {}

fRGBA::fRGBA() : fRGBA(0.0, 0.0, 0.0, 0.0) {}

float fRGBA::A() const { return _a; }

float& fRGBA::A() { return _a; }

unsigned fRGBA::uA() const { return static_cast<unsigned>(_a * 255.99); }

// Operator overloads

void fRGB::operator+=(fRGB& other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
}

void fRGB::operator-=(fRGB& other) {
  _r -= other.R();
  _g -= other.G();
  _b -= other.B();
}

void fRGB::operator+=(float value) {
  _r += value;
  _g += value;
  _b += value;
}

void fRGB::operator-=(float value) { operator+=(-value); }

void fRGB::operator*=(float value) {
  _r *= value;
  _g *= value;
  _b *= value;
}

void fRGB::operator/=(float value) { operator*=(1.0f / value); }

void fRGBA::operator+=(fRGBA& other) {
  _r += other.R();
  _g += other.G();
  _b += other.B();
  _a += other.A();
}

void fRGBA::operator-=(fRGBA& other) {
  _r -= other.R();
  _g -= other.G();
  _b -= other.B();
  _a -= other.A();
}

void fRGBA::operator+=(float value) {
  fRGB::operator+=(value);
  _a += value;
}

void fRGBA::operator-=(float value) {
  fRGB::operator-=(value);
  _a -= value;
}

void fRGBA::operator*=(float value) {
  fRGB::operator*=(value);
  _a *= value;
}

void fRGBA::operator/=(float value) {
  float v = 1 / value;
  operator*=(v);
}

// Static operator overloads

inline fRGB operator+(const fRGB& a, const fRGB& b) {
  return {a.R() + b.R(), a.G() + b.G(), a.B() + b.B()};
}

inline fRGB operator-(const fRGB& a, const fRGB& b) {
  return {a.R() - b.R(), a.G() - b.G(), a.B() - b.B()};
}

inline fRGB operator*(const fRGB& a, const fRGB& b) {
  return {a.R() * b.R(), a.G() * b.G(), a.B() * b.B()};
}

inline fRGB operator/(const fRGB& a, const fRGB& b) {
  return {a.R() / b.R(), a.G() / b.G(), a.B() / b.B()};
}

inline fRGB operator+(const fRGB& rgb, const float value) {
  return {rgb.R() + value, rgb.G() + value, rgb.B() + value};
}

inline fRGB operator-(const fRGB& rgb, const float value) {
  return {rgb.R() - value, rgb.G() - value, rgb.B() - value};
}

inline fRGB operator*(const fRGB& rgb, const float value) {
  return {rgb.R() * value, rgb.G() * value, rgb.B() * value};
}

inline fRGB operator/(const fRGB& rgb, const float value) {
  return {rgb.R() / value, rgb.G() / value, rgb.B() / value};
}

inline fRGBA operator+(const fRGBA& a, const fRGBA& b) {
  return {a.R() + b.R(), a.G() + b.G(), a.B() + b.B(), a.A() + b.A()};
}

inline fRGBA operator-(const fRGBA& a, const fRGBA& b) {
  return {a.R() - b.R(), a.G() - b.G(), a.B() - b.B(), a.A() - b.A()};
}

inline fRGBA operator*(const fRGBA& a, const fRGBA& b) {
  return {a.R() * b.R(), a.G() * b.G(), a.B() * b.B(), a.A() * b.A()};
}

inline fRGBA operator/(const fRGBA& a, const fRGBA& b) {
  return {a.R() / b.R(), a.G() / b.G(), a.B() / b.B(), a.A() / b.A()};
}

inline fRGBA operator+(const fRGBA& rgba, const float value) {
  return {rgba.R() + value, rgba.G() + value, rgba.B() + value,
          rgba.A() + value};
}

inline fRGBA operator-(const fRGBA& rgba, const float value) {
  return {rgba.R() - value, rgba.G() - value, rgba.B() - value,
          rgba.A() - value};
}

inline fRGBA operator*(const fRGBA& rgba, const float value) {
  return {rgba.R() * value, rgba.G() * value, rgba.B() * value,
          rgba.A() * value};
}

inline fRGBA operator/(const fRGBA& rgba, const float value) {
  return {rgba.R() / value, rgba.G() / value, rgba.B() / value,
          rgba.A() / value};
}

}  // namespace Pixel