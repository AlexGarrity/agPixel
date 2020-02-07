#include "Pixel/FPixel.hpp"

namespace ag {
namespace Pixel {

float fRGBA::R() const { return a; }
float fRGBA::G() const { return b; }
float fRGBA::B() const { return c; }
float fRGBA::A() const { return d; }

float &fRGBA::R() { return a; }
float &fRGBA::G() { return b; }
float &fRGBA::B() { return c; }
float &fRGBA::A() { return d; }

uint8_t fRGBA::uR() const { return static_cast<uint8_t>(a * 255.99f); }
uint8_t fRGBA::uG() const { return static_cast<uint8_t>(b * 255.99f); }
uint8_t fRGBA::uB() const { return static_cast<uint8_t>(c * 255.99f); }
uint8_t fRGBA::uA() const { return static_cast<uint8_t>(d * 255.99f); }

void fRGBA::operator+=(fRGBA &other) {
  auto r = Add(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void fRGBA::operator-=(fRGBA &other) {
  auto r = Sub(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void fRGBA::operator*=(fRGBA &other) {
  auto r = Mul(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void fRGBA::operator/=(fRGBA &other) {
  auto r = Div(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void fRGBA::operator+=(float v) {
  auto r = Add(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void fRGBA::operator-=(float v) {
  auto r = Sub(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void fRGBA::operator*=(float v) {
  auto r = Mul(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void fRGBA::operator/=(float v) {
  auto r = Div(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

}; // namespace Pixel
}; // namespace ag