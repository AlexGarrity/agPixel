#include "Pixel/DPixel.hpp"

namespace ag {
namespace Pixel {

double dRGBA::R() const { return a; }
double dRGBA::G() const { return b; }
double dRGBA::B() const { return c; }
double dRGBA::A() const { return d; }

double &dRGBA::R() { return a; }
double &dRGBA::G() { return b; }
double &dRGBA::B() { return c; }
double &dRGBA::A() { return d; }

uint8_t dRGBA::uR() const { return static_cast<uint8_t>(a * 255.99f); }
uint8_t dRGBA::uG() const { return static_cast<uint8_t>(b * 255.99f); }
uint8_t dRGBA::uB() const { return static_cast<uint8_t>(c * 255.99f); }
uint8_t dRGBA::uA() const { return static_cast<uint8_t>(d * 255.99f); }

void dRGBA::operator+=(dRGBA &other) {
  auto r = Add(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void dRGBA::operator-=(dRGBA &other) {
  auto r = Sub(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void dRGBA::operator*=(dRGBA &other) {
  auto r = Mul(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void dRGBA::operator/=(dRGBA &other) {
  auto r = Div(*this, *(&other));
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void dRGBA::operator+=(double v) {
  auto r = Add(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void dRGBA::operator-=(double v) {
  auto r = Sub(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void dRGBA::operator*=(double v) {
  auto r = Mul(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

void dRGBA::operator/=(double v) {
  auto r = Div(*this, v);
  a = r.a;
  b = r.b;
  c = r.c;
  d = r.d;
}

}; // namespace Pixel
}; // namespace ag