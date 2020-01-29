#pragma once

#include "Core.hpp"
#include "Pixel/Int.hpp"
#include "Math.hpp"
#include "PackedMath.hpp"

#include <vector>
#include <cstdint>

namespace ag {
namespace Pixel {

class PixelArray {
    public:
        PixelArray(uint32_t width, uint32_t height);

        void SetSize(uint32_t width = 0, uint32_t height = 0);
        uint32_t GetSize() const;

        RGBA &GetPixel(uint32_t x, uint32_t y);
        RGBA GetPixel(uint32_t x, uint32_t y) const;

        RGBA &GetPixel(uint32_t v);
        RGBA GetPixel(uint32_t v) const;

        void operator+=(PixelArray &other);
        void operator-=(PixelArray &other);
        void operator*=(PixelArray &other);
        void operator/=(PixelArray &other);
        
        void operator+=(const BYTE value);
        void operator-=(const BYTE value);
        void operator*=(const BYTE value);
        void operator/=(const BYTE value);

    private:
        std::vector<RGBA> m_pixelData;

        uint32_t m_width;
        uint32_t m_height;
};

}
}