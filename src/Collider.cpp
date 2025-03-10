#include "Collider.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "PlayerBehaviour.hpp"
#include "Camera.hpp"

using namespace std;

bool Collider::debug = false;

Collider::Collider(Vector size, Vector offset, bool isStatic)
    : size(size), offset(offset), isStatic(isStatic) {}

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

void Collider::render(SDL_Renderer *renderer)
{
    if (debug)
    {
        Camera *camera = owner->getComponent<Camera>();
        if (!camera)
            return;

        SDL_SetRenderDrawColor(renderer, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
        SDL_Rect rect = camera->worldRectToScreenRect(getBoundingBox());
        SDL_RenderDrawRect(renderer, &rect);
    }
}

BoundingBox Collider::getBoundingBox() const
{
    return BoundingBox(position, size);
}

Vector Collider::getGap(const BoundingBox b)
{
    BoundingBox a = getBoundingBox();

    float xGap = a.x > b.x ? a.x - (b.x + b.w) : (a.x + a.w) - b.x;
    float yGap = a.y > b.y ? a.y - (b.y + b.h) : (a.y + a.h) - b.y;

    return {xGap, yGap};
}

// Returns a positive (right/down) or negative (left/up) overlap, or 0s if none
Vector Collider::getOverlap(const BoundingBox b)
{
    BoundingBox a = getBoundingBox();

    Vector gap = getGap(b);

    float xOverlap = a.x > b.x ? min(0.0f, gap.x) : max(0.0f, gap.x);
    float yOverlap = a.y > b.y ? min(0.0f, gap.y) : max(0.0f, gap.y);

    if (xOverlap == 0 || yOverlap == 0)
        return {0, 0};

    debugColor = SDL_Color({255, 0, 0, 255});
    return {xOverlap, yOverlap};
}