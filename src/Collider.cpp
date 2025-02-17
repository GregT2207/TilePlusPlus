#include "Collider.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "PlayerBehaviour.hpp"

bool Collider::debug = true;

Collider::Collider(Vector size, Vector offset, bool isStatic)
    : size(size), offset(offset), isStatic(isStatic)
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
        SDL_SetRenderDrawColor(renderer, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
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

Vector Collider::overlap(const Collider &other)
{
    return overlap(other.getBoundingBox());
}

Vector Collider::overlap(const SDL_Rect b)
{
    SDL_Rect a = getBoundingBox();

    float xOverlap = a.x > b.x ? std::min(0, (a.x - (b.x + b.w))) : std::max(0, ((a.x + a.w) - b.x));
    float yOverlap = a.y > b.y ? std::min(0, (a.y - (b.y + b.h))) : std::max(0, ((a.y + a.h) - b.y));

    grounded = (a.y + a.h) >= b.y;

    if (xOverlap != 0 && yOverlap != 0)
    {
        debugColor = SDL_Color({255, 0, 0, 255});
        return {xOverlap, yOverlap};
    }

    debugColor = grounded ? SDL_Color({0, 180, 0, 255}) : SDL_Color({0, 0, 180, 255});
    return {0, 0};
}