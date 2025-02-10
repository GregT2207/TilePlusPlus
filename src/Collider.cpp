#include "Collider.hpp"
#include "Component.hpp"
#include "GameObject.hpp"

bool Collider::debug = true;

Collider::Collider(Vector size, Vector offset)
    : size(size), offset(offset)
{
}

void Collider::update(float deltaTime, int gravity, int worldHeight)
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
    {
        return;
    }

    position = transform->getPosition() + offset;
}

void Collider::render(SDL_Renderer *renderer)
{
    if (debug)
    {
        SDL_Rect box = getBoundingBox();
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &box);
    }
}

SDL_Rect Collider::getBoundingBox() const
{
    SDL_Rect box;

    box.x = static_cast<int>(position.x - size.x / 2);
    box.y = static_cast<int>(position.y - size.y / 2);
    box.w = static_cast<int>(size.x);
    box.h = static_cast<int>(size.y);

    return box;
}

bool Collider::intersects(const Collider &other) const
{
    SDL_Rect a = getBoundingBox();
    SDL_Rect b = other.getBoundingBox();

    if (a.x + a.w <= b.x)
        return false;
    if (b.x + b.w <= a.x)
        return false;
    if (a.y + a.h <= b.y)
        return false;
    if (b.y + b.h <= a.y)
        return false;

    return true;
}