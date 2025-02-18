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
    followTransform();
}

void Collider::followTransform()
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
        BoundingBox box = getBoundingBox();
        SDL_SetRenderDrawColor(renderer, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
        SDL_Rect rect = {static_cast<int>(box.x), static_cast<int>(box.y), static_cast<int>(box.w), static_cast<int>(box.h)};
        SDL_RenderDrawRect(renderer, &rect);
    }
}

BoundingBox Collider::getBoundingBox() const
{
    BoundingBox box;

    box.x = (position.x - size.x / 2);
    box.y = (position.y - size.y / 2);
    box.w = (size.x);
    box.h = (size.y);

    return box;
}

// Returns a positive (right/down) or negative (left/up) overlap, or 0s if none
Vector Collider::getOverlap(const BoundingBox b)
{
    BoundingBox a = getBoundingBox();

    float xOverlap = a.x > b.x ? std::min(0.0f, (a.x - (b.x + b.w))) : std::max(0.0f, ((a.x + a.w) - b.x));
    float yOverlap = a.y > b.y ? std::min(0.0f, (a.y - (b.y + b.h))) : std::max(0.0f, ((a.y + a.h) - b.y));

    grounded = (a.y + a.h) >= (b.y - 0.1f);

    if (xOverlap != 0 && yOverlap != 0)
    {
        debugColor = SDL_Color({255, 0, 0, 255});
        return {xOverlap, yOverlap};
    }

    debugColor = grounded ? SDL_Color({0, 180, 0, 255}) : SDL_Color({0, 0, 180, 255});
    return {0, 0};
}