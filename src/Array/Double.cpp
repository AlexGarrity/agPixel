#include "Array/Double.hpp"

#include <functional>

namespace Pixel {

dPixelArray::dPixelArray(uint32_t width, uint32_t height) {
        SetSize(width, height);
}

void dPixelArray::SetSize(uint32_t width, uint32_t height) {
        m_height = (height) ? height : m_height;
        m_width = (width) ? width : m_width;

        m_pixelData.resize(m_width * m_height);
}

uint32_t dPixelArray::GetSize() const {
        return m_width * m_height;
}

dRGBA dPixelArray::GetPixel(uint32_t x, uint32_t y) const {
        if (x > m_width)
                return m_pixelData[0];
        if (y > m_height)
                return m_pixelData[0];

        return m_pixelData[(y * m_width) + x];
}

dRGBA &dPixelArray::GetPixel(uint32_t x, uint32_t y) {
        if (x > m_width)
                return m_pixelData[0];
        if (y > m_height)
                return m_pixelData[0];

        return m_pixelData[(y * m_width) + x];
}

dRGBA dPixelArray::GetPixel(uint32_t v) const {
        if (v > m_width * m_height)
                return dRGBA();

        return m_pixelData[v];
}

dRGBA &dPixelArray::GetPixel(uint32_t v) {
        if (v > m_width * m_height)
                return m_pixelData[0];

        return m_pixelData[v];
}

DQuad PixelToDQuad(const dRGBA pixel) {
        return DQuad(pixel.R(), pixel.G(), pixel.B(), pixel.A());
}

dRGBA DQuadToPixel(const DQuad quad) {
        return dRGBA(quad[0], quad[1], quad[2], quad[3]);
}

void PerformOperationInPlace(dPixelArray &a, dPixelArray &b, DQuad fn(DQuad, DQuad)) {
        uint8_t remainder = a.GetSize() % 2;
        DQuad qA;
        DQuad qB;
        for (auto i = 0; i < (a.GetSize() - remainder); i+=2) {
                qA = PixelToDQuad(a.GetPixel(i));
                qB = PixelToDQuad(b.GetPixel(i));
                auto r = fn(qA, qB);

                a.GetPixel(i) = DQuadToPixel(r);
        }
}

void PerformOperationInPlace(dPixelArray &a, DQuad &qB, DQuad f1(DQuad, DQuad), DQuad f2(DQuad, DQuad)) {
        uint8_t remainder = a.GetSize() % 2;
        DQuad qA;
        for (auto i = 0; i < (a.GetSize() - remainder); i+=2) {
                qA = PixelToDQuad(a.GetPixel(i));
                auto r = f1(qA, qB);
                a.GetPixel(i) = DQuadToPixel(r);
        }
}

void dPixelArray::operator+=(dPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Add);
}

void dPixelArray::operator-=(dPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Sub);
}

void dPixelArray::operator*=(dPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Mul);
}

void dPixelArray::operator/=(dPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Div);
}


void dPixelArray::operator+=(const double v) {
        DQuad other { v };
        PerformOperationInPlace(*this, other, &Add, &Add);
}

void dPixelArray::operator-=(const double v) {
        DQuad other { v };
        PerformOperationInPlace(*this, other, &Sub, &Sub);
}

void dPixelArray::operator*=(const double v) {       
        DQuad other { v };
        PerformOperationInPlace(*this, other, &Mul, &Mul);
}

void dPixelArray::operator/=(const double v) {      
        DQuad other { v };
        PerformOperationInPlace(*this, other, &Div, &Div);
}


PIXEL_API dPixelArray operator+(dPixelArray &a, dPixelArray &b) {
        dPixelArray out = a;
        out += b;
        return out;
}

PIXEL_API dPixelArray operator-(dPixelArray &a, dPixelArray &b) {
        dPixelArray out = a;
        out -= b;
        return out;
}

PIXEL_API dPixelArray operator*(dPixelArray &a, dPixelArray &b) {
        dPixelArray out = a;
        out *= b;
        return out;
}

PIXEL_API dPixelArray operator/(dPixelArray &a, dPixelArray &b) {
        dPixelArray out = a;
        out /= b;
        return out;
}


PIXEL_API dPixelArray operator+(dPixelArray &a, double b) {
        dPixelArray out = a;
        out += b;
        return out;
}

PIXEL_API dPixelArray operator-(dPixelArray &a, double b) {
        dPixelArray out = a;
        out -= b;
        return out;
}

PIXEL_API dPixelArray operator*(dPixelArray &a, double b) {
        dPixelArray out = a;
        out *= b;
        return out;
}

PIXEL_API dPixelArray operator/(dPixelArray &a, double b) {
        dPixelArray out = a;
        out /= b;
        return out;
}


}