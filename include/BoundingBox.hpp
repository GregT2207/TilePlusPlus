#pragma once

struct BoundingBox
{
    BoundingBox(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
    BoundingBox(int x = 0, int y = 0, int w = 0, int h = 0) : x(x), y(y), w(w), h(h) {}

    float x;
    float y;
    float w;
    float h;
};