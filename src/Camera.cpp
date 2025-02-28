#include "Camera.hpp"
#include "GameObject.hpp"

class Transform;

void Camera::handleEvents(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            targetZoom = zoom * 2;
            break;
        case SDLK_DOWN:
            targetZoom = zoom / 2;
            break;
        }
    }
}

void Camera::render(SDL_Renderer *renderer)
{
    if (zoom > targetZoom - 0.1f && zoom < targetZoom + 0.1f)
    {
        zoom = targetZoom;
    }

    if (zoom != targetZoom)
    {
        zoom += (targetZoom - zoom) * 0.1f;
        width = originalWidth / zoom;
        height = originalHeight / zoom;
    }
}

Vector Camera::getPosition() const
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return {0.0f, 0.0f};

    return transform->getPosition();
}

Vector Camera::screenPosToWorldPos(Vector screenPos) const
{
    Vector cameraWorldPos = getPosition();
    Vector cameraScreenPos = Vector({originalWidth / 2, originalHeight / 2});
    Vector difference = screenPos - cameraScreenPos;

    return {cameraWorldPos.x + difference.x, cameraWorldPos.y + difference.y};
}

Vector Camera::worldPosToScreenPos(Vector worldPos) const
{
    Vector cameraWorldPos = getPosition();
    Vector cameraScreenPos = Vector({originalWidth / 2, originalHeight / 2});
    Vector difference = worldPos - cameraWorldPos;

    return {cameraScreenPos.x + difference.x, cameraScreenPos.y + difference.y};
}

SDL_Rect Camera::worldRectToScreenRect(BoundingBox rect) const
{
    Vector screenPoint = worldPosToScreenPos({rect.x, rect.y});
    screenPoint *= zoom;
    screenPoint += Vector({originalWidth * 0.5f, originalHeight * 0.5f}) * (1 - zoom);

    return {static_cast<int>(screenPoint.x), static_cast<int>(screenPoint.y), static_cast<int>(rect.w * zoom), static_cast<int>(rect.h * zoom)};
}