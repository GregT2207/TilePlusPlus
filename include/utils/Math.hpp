#pragma once
#include "geometry/Vector.hpp"

namespace Math
{
    inline float lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }
}