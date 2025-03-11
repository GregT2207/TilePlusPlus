#pragma once
#include <cmath>
#include "Math.hpp"

struct Vector
{
    Vector(float x, float y) : x(x), y(y) {};
    Vector(int x = 0, int y = 0) : x(static_cast<float>(x)), y(static_cast<float>(y)) {};

    float magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    Vector &normalize()
    {
        float length = magnitude();
        if (length != 0)
        {
            x /= length;
            y /= length;
        }

        return *this;
    }

    Vector normalized() const
    {
        Vector copy = *this;
        copy.normalize();

        return copy;
    }

    Vector &sgn()
    {
        if (x != 0)
            x = x > 0 ? 1.0f : -1.0f;

        if (y != 0)
            y = y > 0 ? 1.0f : -1.0f;

        return *this;
    }

    Vector sgned() const
    {
        Vector copy = *this;
        copy.sgn();

        return copy;
    }

    Vector &lerp(Vector target, float t)
    {
        *this = Math::lerp(*this, target, t);

        return *this;
    }

    inline Vector *operator+=(const Vector &b)
    {
        x += b.x;
        y += b.y;
        return this;
    }

    inline Vector *operator-=(const Vector &b)
    {
        x -= b.x;
        y -= b.y;
        return this;
    }

    inline Vector *operator*=(const Vector &b)
    {
        x *= b.x;
        y *= b.y;
        return this;
    }

    inline Vector *operator/=(const Vector &b)
    {
        x /= b.x;
        y /= b.y;
        return this;
    }

    inline Vector *operator+=(float b)
    {
        x += b;
        y += b;
        return this;
    }

    inline Vector *operator-=(float b)
    {
        x -= b;
        y -= b;
        return this;
    }

    inline Vector *operator*=(float b)
    {
        x *= b;
        y *= b;
        return this;
    }

    inline Vector *operator/=(float b)
    {
        x /= b;
        y /= b;
        return this;
    }

    float x;
    float y;
};

inline Vector operator+(const Vector &a, const Vector &b)
{
    return {a.x + b.x, a.y + b.y};
}

inline Vector operator-(const Vector &a, const Vector &b)
{
    return {a.x - b.x, a.y - b.y};
}

inline Vector operator*(const Vector &a, const Vector &b)
{
    return {a.x * b.x, a.y * b.y};
}

inline Vector operator/(const Vector &a, const Vector &b)
{
    return {a.x / b.x, a.y / b.y};
}

inline Vector operator+(const Vector &a, float b)
{
    return {a.x + b, a.y + b};
}

inline Vector operator-(const Vector &a, float b)
{
    return {a.x - b, a.y - b};
}

inline Vector operator*(const Vector &a, float b)
{
    return {a.x * b, a.y * b};
}

inline Vector operator/(const Vector &a, float b)
{
    return {a.x / b, a.y / b};
}