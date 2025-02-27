#pragma once
#include <SDL2/SDL.h>
#include "Component.hpp"
#include "Vector.hpp"

class Game;
class GameObject;
class BoundingBox;

class Camera : public Component
{
public:
    Camera(int width, int height) : originalWidth(width), originalHeight(height) { setZoom(zoom); }

    Vector screenPosToWorldPos(Vector screenPos) const;
    Vector worldPosToScreenPos(Vector worldPos) const;
    SDL_Rect worldRectToScreenRect(BoundingBox rect) const;

private:
    Vector getPosition() const;
    void setZoom(float newZoom);

    const int originalWidth;
    const int originalHeight;
    int width;
    int height;
    float zoom = 1.0f;
};