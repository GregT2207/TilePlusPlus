#pragma once

struct Vector
{
    float x = 0.0f;
    float y = 0.0f;

    float magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    Vector normalize()
    {
        float length = sqrt(x * x + y * y);
        return {x / length, y / length};
    }
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

inline Vector operator+=(Vector &a, const Vector &b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline Vector operator-=(Vector &a, const Vector &b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

inline Vector operator*=(Vector &a, const Vector &b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

inline Vector operator/=(Vector &a, const Vector &b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

inline bool operator>(Vector &a, Vector &b)
{
    return a.x > b.x && a.y > b.y;
}

inline bool operator<(Vector &a, Vector &b)
{
    return a.x < b.x && a.y < b.y;
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

inline Vector operator+=(Vector &a, float b)
{
    a.x += b;
    a.y += b;
    return a;
}

inline Vector operator-=(Vector &a, float b)
{
    a.x -= b;
    a.y -= b;
    return a;
}

inline Vector operator*=(Vector &a, float b)
{
    a.x *= b;
    a.y *= b;
    return a;
}

inline Vector operator/=(Vector &a, float b)
{
    a.x /= b;
    a.y /= b;
    return a;
}

inline bool operator>(Vector &a, float b)
{
    return a.x > b && a.y > b;
}

inline bool operator<(Vector &a, float b)
{
    return a.x < b && a.y < b;
}