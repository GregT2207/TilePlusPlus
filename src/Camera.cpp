#include "Camera.hpp"
#include "GameObject.hpp"

class Transform;

Vector Camera::getPosition() const
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return {0.0f, 0.0f};

    return transform->getPosition();
}

void Camera::setZoom(float newZoom)
{
    zoom = newZoom;
    width = originalWidth * zoom;
    height = originalHeight * zoom;
}

Vector Camera::screenPosToWorldPos(Vector screenPos) const
{
    Vector cameraWorldPos = getPosition();
    Vector cameraScreenPos = Vector({width / 2, height / 2});
    Vector difference = screenPos - cameraScreenPos;

    return {cameraWorldPos.x + difference.x, cameraWorldPos.y + difference.y};
}

Vector Camera::worldPosToScreenPos(Vector worldPos) const
{
    Vector cameraWorldPos = getPosition();
    Vector cameraScreenPos = Vector({width / 2, height / 2});
    Vector difference = worldPos - cameraWorldPos;

    return {cameraScreenPos.x + difference.x, cameraScreenPos.y + difference.y};
}

SDL_Rect Camera::worldRectToScreenRect(BoundingBox rect) const
{
    Vector screenPoint = worldPosToScreenPos({rect.x, rect.y});
    return {static_cast<int>(screenPoint.x), static_cast<int>(screenPoint.y), static_cast<int>(rect.w * zoom), static_cast<int>(rect.h * zoom)};
}