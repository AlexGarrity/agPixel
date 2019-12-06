#include "Array/Float.hpp"

#include <functional>

namespace Pixel {

fPixelArray::fPixelArray(uint32_t width, uint32_t height) {
        SetSize(width, height);
}

void fPixelArray::SetSize(uint32_t width, uint32_t height) {
        m_height = (height) ? height : m_height;
        m_width = (width) ? width : m_width;

        m_pixelData.resize(m_width * m_height);
}

uint32_t fPixelArray::GetSize() const {
        return m_width * m_height;
}

fRGBA fPixelArray::GetPixel(uint32_t x, uint32_t y) const {
        if (x > m_width)
                return m_pixelData[0];
        if (y > m_height)
                return m_pixelData[0];

        return m_pixelData[(y * m_width) + x];
}

fRGBA &fPixelArray::GetPixel(uint32_t x, uint32_t y) {
        if (x > m_width)
                return m_pixelData[0];
        if (y > m_height)
                return m_pixelData[0];

        return m_pixelData[(y * m_width) + x];
}

fRGBA fPixelArray::GetPixel(uint32_t v) const {
        if (v > m_width * m_height)
                return fRGBA();

        return m_pixelData[v];
}

fRGBA &fPixelArray::GetPixel(uint32_t v) {
        if (v > m_width * m_height)
                return m_pixelData[0];

        return m_pixelData[v];
}

FQuad PixelToFQuad(const fRGBA pixel) {
        return FQuad(pixel.R(), pixel.G(), pixel.B(), pixel.A());
}

fRGBA FQuadToPixel(const FQuad quad) {
        return fRGBA(quad[0], quad[1], quad[2], quad[3]);
}

void PerformOperationInPlace(fPixelArray &a, fPixelArray &b, FQuad2 f1(FQuad2, FQuad2), FQuad f2(FQuad, FQuad)) {
        uint8_t remainder = a.GetSize() % 2;
        FQuad2 qA;
        FQuad2 qB;
        for (auto i = 0; i < (a.GetSize() - remainder); i+=2) {
                qA.a = PixelToFQuad(a.GetPixel(i));
                qB.a = PixelToFQuad(b.GetPixel(i));
                qA.b = PixelToFQuad(a.GetPixel(i+1));
                qB.b = PixelToFQuad(b.GetPixel(i+1));
                auto r = f1(qA, qB);

                a.GetPixel(i) = FQuadToPixel(r.a);
                a.GetPixel(i+1) = FQuadToPixel(r.b);
        }

        for (auto i = a.GetSize() - remainder; i < a.GetSize(); ++i) {
                FQuad pA = PixelToFQuad(a.GetPixel(i));
                auto r = f2(pA, qB.a);
                a.GetPixel(i) = FQuadToPixel(r);
        }
}

void PerformOperationInPlace(fPixelArray &a, FQuad2 &qB, FQuad2 f1(FQuad2, FQuad2), FQuad f2(FQuad, FQuad)) {
        uint8_t remainder = a.GetSize() % 2;
        FQuad2 qA;
        for (auto i = 0; i < (a.GetSize() - remainder); i+=2) {
                qA.a = PixelToFQuad(a.GetPixel(i));
                qA.b = PixelToFQuad(a.GetPixel(i+1));
                auto r = f1(qA, qB);

                a.GetPixel(i) = FQuadToPixel(r.a);
                a.GetPixel(i+1) = FQuadToPixel(r.b);
        }

        for (auto i = a.GetSize() - remainder; i < a.GetSize(); ++i) {
                FQuad pA = PixelToFQuad(a.GetPixel(i));
                auto r = f2(pA, qB.a);
                a.GetPixel(i) = FQuadToPixel(r);
        }
}

void fPixelArray::operator+=(fPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Add, &Add);
}

void fPixelArray::operator-=(fPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Sub, &Sub);
}

void fPixelArray::operator*=(fPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Mul, &Mul);
}

void fPixelArray::operator/=(fPixelArray &other) {
        if (GetSize() != other.GetSize())
                return;
        
        PerformOperationInPlace(*this, other, &Div, &Div);
}


void fPixelArray::operator+=(const float v) {
        FQuad2 other { v, v };
        PerformOperationInPlace(*this, other, &Add, &Add);
}

void fPixelArray::operator-=(const float v) {
        FQuad2 other { v, v };
        PerformOperationInPlace(*this, other, &Sub, &Sub);
}

void fPixelArray::operator*=(const float v) {       
        FQuad2 other { v, v };
        PerformOperationInPlace(*this, other, &Mul, &Mul);
}

void fPixelArray::operator/=(const float v) {      
        FQuad2 other { v, v };
        PerformOperationInPlace(*this, other, &Div, &Div);
}


}