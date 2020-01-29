#include "Array/Int.hpp"

#include <functional>

namespace ag {
namespace Pixel {

PixelArray::PixelArray(uint32_t width, uint32_t height) {
  SetSize(width, height);
}

void PixelArray::SetSize(uint32_t width, uint32_t height) {
  m_height = (height) ? height : m_height;
  m_width = (width) ? width : m_width;

  m_pixelData.resize(m_width * m_height);
}

uint32_t PixelArray::GetSize() const { return m_width * m_height; }

RGBA PixelArray::GetPixel(uint32_t x, uint32_t y) const {
  if (x > m_width)
    return m_pixelData[0];
  if (y > m_height)
    return m_pixelData[0];

  return m_pixelData[(y * m_width) + x];
}

RGBA &PixelArray::GetPixel(uint32_t x, uint32_t y) {
  if (x > m_width)
    return m_pixelData[0];
  if (y > m_height)
    return m_pixelData[0];

  return m_pixelData[(y * m_width) + x];
}

RGBA PixelArray::GetPixel(uint32_t v) const {
  if (v > m_width * m_height)
    return RGBA();

  return m_pixelData[v];
}

RGBA &PixelArray::GetPixel(uint32_t v) {
  if (v > m_width * m_height)
    return m_pixelData[0];

  return m_pixelData[v];
}

BQuad PixelToBQuad(const RGBA pixel) {
  return BQuad(pixel.R(), pixel.G(), pixel.B(), pixel.A());
}

RGBA BQuadToPixel(const BQuad quad) {
  return RGBA(quad[0], quad[1], quad[2], quad[3]);
}

void PerformOperationInPlace(PixelArray &a, PixelArray &b,
                             BQuad8 f1(BQuad8, BQuad8),
                             BQuad f2(BQuad, BQuad)) {
  uint8_t remainder = a.GetSize() % 8;
  BQuad8 qA;
  BQuad8 qB;
  for (auto i = 0; i < (a.GetSize() - remainder); i += 8) {
    qA.a = PixelToBQuad(a.GetPixel(i + 0));
    qB.a = PixelToBQuad(b.GetPixel(i + 0));
    qA.b = PixelToBQuad(a.GetPixel(i + 1));
    qB.b = PixelToBQuad(b.GetPixel(i + 1));
    qA.c = PixelToBQuad(a.GetPixel(i + 2));
    qB.c = PixelToBQuad(b.GetPixel(i + 2));
    qA.d = PixelToBQuad(a.GetPixel(i + 3));
    qB.d = PixelToBQuad(b.GetPixel(i + 3));
    qA.e = PixelToBQuad(a.GetPixel(i + 4));
    qB.e = PixelToBQuad(b.GetPixel(i + 4));
    qA.f = PixelToBQuad(a.GetPixel(i + 5));
    qB.f = PixelToBQuad(b.GetPixel(i + 5));
    qA.g = PixelToBQuad(a.GetPixel(i + 6));
    qA.h = PixelToBQuad(a.GetPixel(i + 7));
    auto r = f1(qA, qB);

    a.GetPixel(i + 0) = BQuadToPixel(r.a);
    a.GetPixel(i + 1) = BQuadToPixel(r.b);
    a.GetPixel(i + 2) = BQuadToPixel(r.c);
    a.GetPixel(i + 3) = BQuadToPixel(r.d);
    a.GetPixel(i + 4) = BQuadToPixel(r.e);
    a.GetPixel(i + 5) = BQuadToPixel(r.f);
    a.GetPixel(i + 6) = BQuadToPixel(r.g);
    a.GetPixel(i + 7) = BQuadToPixel(r.h);
  }

  for (auto i = a.GetSize() - remainder; i < a.GetSize(); ++i) {
    BQuad pA = PixelToBQuad(a.GetPixel(i));
    auto r = f2(pA, qB.a);
    a.GetPixel(i) = BQuadToPixel(r);
  }
}

void PerformOperationInPlace(PixelArray &a, BQuad8 &qB,
                             BQuad8 f1(BQuad8, BQuad8),
                             BQuad f2(BQuad, BQuad)) {
  uint8_t remainder = a.GetSize() % 8;
  BQuad8 qA;
  for (auto i = 0; i < (a.GetSize() - remainder); i += 8) {
    qA.a = PixelToBQuad(a.GetPixel(i + 0));
    qA.b = PixelToBQuad(a.GetPixel(i + 1));
    qA.c = PixelToBQuad(a.GetPixel(i + 2));
    qA.d = PixelToBQuad(a.GetPixel(i + 3));
    qA.e = PixelToBQuad(a.GetPixel(i + 4));
    qA.f = PixelToBQuad(a.GetPixel(i + 5));
    qA.g = PixelToBQuad(a.GetPixel(i + 6));
    qA.h = PixelToBQuad(a.GetPixel(i + 7));
    auto r = f1(qA, qB);

    a.GetPixel(i + 0) = BQuadToPixel(r.a);
    a.GetPixel(i + 1) = BQuadToPixel(r.b);
    a.GetPixel(i + 2) = BQuadToPixel(r.c);
    a.GetPixel(i + 3) = BQuadToPixel(r.d);
    a.GetPixel(i + 4) = BQuadToPixel(r.e);
    a.GetPixel(i + 5) = BQuadToPixel(r.f);
    a.GetPixel(i + 6) = BQuadToPixel(r.g);
    a.GetPixel(i + 7) = BQuadToPixel(r.h);
  }

  for (auto i = a.GetSize() - remainder; i < a.GetSize(); ++i) {
    BQuad pA = PixelToBQuad(a.GetPixel(i));
    auto r = f2(pA, qB.a);
    a.GetPixel(i) = BQuadToPixel(r);
  }
}

void PixelArray::operator+=(PixelArray &other) {
  if (GetSize() != other.GetSize())
    return;

  PerformOperationInPlace(*this, other, &Add, &Add);
}

void PixelArray::operator-=(PixelArray &other) {
  if (GetSize() != other.GetSize())
    return;

  PerformOperationInPlace(*this, other, &Sub, &Sub);
}

void PixelArray::operator*=(PixelArray &other) {
  if (GetSize() != other.GetSize())
    return;

  PerformOperationInPlace(*this, other, &Mul, &Mul);
}

void PixelArray::operator/=(PixelArray &other) {
  if (GetSize() != other.GetSize())
    return;

  PerformOperationInPlace(*this, other, &Div, &Div);
}

void PixelArray::operator+=(const uint8_t v) {
  BQuad8 other{v, v, v, v, v, v, v, v};
  PerformOperationInPlace(*this, other, &Add, &Add);
}

void PixelArray::operator-=(const uint8_t v) {
  BQuad8 other{v, v, v, v, v, v, v, v};
  PerformOperationInPlace(*this, other, &Sub, &Sub);
}

void PixelArray::operator*=(const uint8_t v) {
  BQuad8 other{v, v, v, v, v, v, v, v};
  PerformOperationInPlace(*this, other, &Mul, &Mul);
}

void PixelArray::operator/=(const uint8_t v) {
  BQuad8 other{v, v, v, v, v, v, v, v};
  PerformOperationInPlace(*this, other, &Div, &Div);
}

PIXEL_API PixelArray operator+(PixelArray &a, PixelArray &b) {
  PixelArray out = a;
  out += b;
  return out;
}

PIXEL_API PixelArray operator-(PixelArray &a, PixelArray &b) {
  PixelArray out = a;
  out -= b;
  return out;
}

PIXEL_API PixelArray operator*(PixelArray &a, PixelArray &b) {
  PixelArray out = a;
  out *= b;
  return out;
}

PIXEL_API PixelArray operator/(PixelArray &a, PixelArray &b) {
  PixelArray out = a;
  out /= b;
  return out;
}

PIXEL_API PixelArray operator+(PixelArray &a, double b) {
  PixelArray out = a;
  out += b;
  return out;
}

PIXEL_API PixelArray operator-(PixelArray &a, double b) {
  PixelArray out = a;
  out -= b;
  return out;
}

PIXEL_API PixelArray operator*(PixelArray &a, double b) {
  PixelArray out = a;
  out *= b;
  return out;
}

PIXEL_API PixelArray operator/(PixelArray &a, double b) {
  PixelArray out = a;
  out /= b;
  return out;
}

} // namespace Pixel
} // namespace ag