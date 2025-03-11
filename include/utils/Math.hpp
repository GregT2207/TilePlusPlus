#pragma once
#include "Vector.hpp"

namespace Math
{
    inline float lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    inline Vector lerp(Vector a, Vector b, float t)
    {
        return a + (b - a) * t;
    }
}