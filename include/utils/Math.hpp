#pragma once
#include "geometry/Vector.hpp"

namespace Math
{
    inline float lerp(float a, float b, float t)
    {
        t = std::max(t, 0.0f);
        t = std::min(t, 1.0f);

        if (fabs(a - b) < t)
            return b;

        return a + (b - a) * t;
    }
}