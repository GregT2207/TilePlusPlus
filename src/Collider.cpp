#include "Collider.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "PlayerBehaviour.hpp"

using namespace std;

bool Collider::debug = false;

Collider::Collider(Vector size, Vector offset, bool isStatic)
    : size(size), offset(offset), isStatic(isStatic)
{
}

void Collider::update(float deltaTime)
{
    debugColor = SDL_Color({0, 0, 255, 255});

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

void Collider::render()
{
    if (debug)
    {
        BoundingBox box = getBoundingBox();
        owner->game->renderer->setRenderDrawColor(debugColor.r, debugColor.g, debugColor.b, debugColor.a);
        SDL_Rect rect = owner->game->getCamera()->getWorldPos({static_cast<int>(box.x), static_cast<int>(box.y), static_cast<int>(box.w), static_cast<int>(box.h)});
        owner->game->renderer->renderDrawRect(&rect);
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

    float xGap = a.x > b.x ? a.x - (b.x + b.w) : (a.x + a.w) - b.x;
    float yGap = a.y > b.y ? a.y - (b.y + b.h) : (a.y + a.h) - b.y;

    float xOverlap = a.x > b.x ? min(0.0f, xGap) : max(0.0f, xGap);
    float yOverlap = a.y > b.y ? min(0.0f, yGap) : max(0.0f, yGap);

    if (xOverlap == 0 || yOverlap == 0)
        return {0, 0};

    debugColor = SDL_Color({255, 0, 0, 255});
    return {xOverlap, yOverlap};
}