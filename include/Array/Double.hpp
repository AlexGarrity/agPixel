#pragma once

#include "Core.hpp"
#include "Pixel/Double.hpp"
#include "Math.hpp"
#include "PackedMath.hpp"

#include <vector>
#include <cstdint>

namespace ag {
namespace Pixel {

class dPixelArray {
    public:
        dPixelArray(uint32_t width, uint32_t height);

        void SetSize(uint32_t width = 0, uint32_t height = 0);
        uint32_t GetSize() const;

        dRGBA &GetPixel(uint32_t x, uint32_t y);
        dRGBA GetPixel(uint32_t x, uint32_t y) const;

        dRGBA &GetPixel(uint32_t v);
        dRGBA GetPixel(uint32_t v) const;

        void operator+=(dPixelArray &other);
        void operator-=(dPixelArray &other);
        void operator*=(dPixelArray &other);
        void operator/=(dPixelArray &other);
        
        void operator+=(const double value);
        void operator-=(const double value);
        void operator*=(const double value);
        void operator/=(const double value);

    private:
        std::vector<dRGBA> m_pixelData;

        uint32_t m_width;
        uint32_t m_height;
};

}
}