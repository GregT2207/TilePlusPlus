#pragma once

struct Vector
{
    Vector(float x, float y) : x(x), y(y) {};
    Vector(int x = 0, int y = 0) : x(x), y(y) {};

    float magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    Vector normalize()
    {
        float length = sqrt(x * x + y * y);
        return {x / length, y / length};
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