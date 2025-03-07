#pragma once

struct BoundingBox
{
    BoundingBox(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
    BoundingBox(int x = 0, int y = 0, int w = 0, int h = 0) : x(static_cast<float>(x)), y(static_cast<float>(y)), w(static_cast<float>(w)), h(static_cast<float>(h)) {}
    BoundingBox(Vector position, Vector size) : x(position.x - size.x / 2), y(position.y - size.y / 2), w(size.x), h(size.y) {}

    float x;
    float y;
    float w;
    float h;
};