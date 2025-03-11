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
    Camera(int width, int height) : originalWidth(width), originalHeight(height), width(width), height(height) {}

    Vector screenPosToWorldPos(Vector screenPos) const;
    Vector worldPosToScreenPos(Vector worldPos) const;
    SDL_Rect worldRectToScreenRect(BoundingBox rect) const;

    int getOriginalWidth() const { return originalWidth; }
    int getOriginalHeight() const { return originalHeight; }
    float getZoom() const { return zoom; }

private:
    void handleEvents(SDL_Event &event) override;
    void render(SDL_Renderer *renderer) override;
    Vector getPosition() const;

    const int originalWidth;
    const int originalHeight;
    int width;
    int height;
    float zoom = 1.0f;
    float targetZoom = zoom;
};