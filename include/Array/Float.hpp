#pragma once

#include "Core.hpp"
#include "Pixel/Float.hpp"
#include "Math.hpp"
#include "PackedMath.hpp"

#include <vector>
#include <cstdint>

namespace Pixel {

class fPixelArray {
    public:
        fPixelArray(uint32_t width, uint32_t height);

        void SetSize(uint32_t width = 0, uint32_t height = 0);
        uint32_t GetSize() const;

        fRGBA &GetPixel(uint32_t x, uint32_t y);
        fRGBA GetPixel(uint32_t x, uint32_t y) const;

        fRGBA &GetPixel(uint32_t v);
        fRGBA GetPixel(uint32_t v) const;

        void operator+=(fPixelArray &other);
        void operator-=(fPixelArray &other);
        void operator*=(fPixelArray &other);
        void operator/=(fPixelArray &other);
        
        void operator+=(const float value);
        void operator-=(const float value);
        void operator*=(const float value);
        void operator/=(const float value);

    private:
        std::vector<fRGBA> m_pixelData;

        uint32_t m_width;
        uint32_t m_height;
};

}