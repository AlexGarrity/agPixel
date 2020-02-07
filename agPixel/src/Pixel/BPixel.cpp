#include "Pixel/BPixel.hpp"

namespace ag {
namespace Pixel {

uint8_t bRGBA::R() const { return a; }
uint8_t bRGBA::G() const { return b; }
uint8_t bRGBA::B() const { return c; }
uint8_t bRGBA::A() const { return d; }

uint8_t &bRGBA::R() { return a; }
uint8_t &bRGBA::G() { return b; }
uint8_t &bRGBA::B() { return c; }
uint8_t &bRGBA::A() { return d; }


float bRGBA::fR() const { return static_cast<float>(a) / 255.0f; }
float bRGBA::fG() const { return static_cast<float>(b) / 255.0f; }
float bRGBA::fB() const { return static_cast<float>(c) / 255.0f; }
float bRGBA::fA() const { return static_cast<float>(d) / 255.0f; }

void bRGBA::operator+=(bRGBA &other) {
  auto r = Add(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void bRGBA::operator-=(bRGBA &other) {
  auto r = Sub(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void bRGBA::operator*=(bRGBA &other) {
  auto r = Mul(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void bRGBA::operator/=(bRGBA &other) {
  auto r = Div(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void bRGBA::operator+=(uint8_t v) {
  auto r = Add(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void bRGBA::operator-=(uint8_t v) {
  auto r = Sub(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void bRGBA::operator*=(uint8_t v) {
  auto r = Mul(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void bRGBA::operator/=(uint8_t v) {
  auto r = Div(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

}; // namespace Pixel
}; // namespace ag