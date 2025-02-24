#include "Camera.hpp"
#include "GameObject.hpp"

class Transform;

Vector Camera::getPos() const
{
    if (!attachment)
        return {0.0f, 0.0f};

    Transform *transform = attachment->getComponent<Transform>();
    if (!transform)
        return {0.0f, 0.0f};

    return transform->getPosition();
}

Vector Camera::getScreenPos(Vector vector) const
{
    return {vector.x + getPos().x - (width / 2), vector.y + getPos().y - (height / 2)};
}

Vector Camera::getWorldPos(Vector vector) const
{
    return {vector.x - getPos().x + (width / 2), vector.y - getPos().y + (height / 2)};
}

SDL_Rect Camera::getWorldPos(SDL_Rect rect) const
{
    Vector offsetPos = getWorldPos(Vector({rect.x, rect.y}));

    return {static_cast<int>(offsetPos.x), static_cast<int>(offsetPos.y), rect.w, rect.h};
}