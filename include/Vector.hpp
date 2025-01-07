#pragma once

struct Vector
{
    float x = 0.0f;
    float y = 0.0f;
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

inline Vector &operator+=(Vector &a, const Vector &b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline Vector &operator-=(Vector &a, const Vector &b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

inline Vector &operator*=(Vector &a, const Vector &b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

inline Vector &operator/=(Vector &a, const Vector &b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}