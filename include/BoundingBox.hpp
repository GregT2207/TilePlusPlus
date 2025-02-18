#pragma once

struct BoundingBox
{
    BoundingBox(float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f) : x(x), y(y), w(w), h(h) {}

    float x;
    float y;
    float w;
    float h;
};