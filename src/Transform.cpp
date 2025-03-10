#include "Transform.hpp"

Transform::Transform(Vector position, Vector velocity, Vector size) : position(position), velocity(velocity), size(size) {}

void Transform::update(float deltaTime)
{
    applyGravity(deltaTime);

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Transform::applyGravity(float deltaTime)
{
    if (velocity.y >= owner->game->getMaxFallSpeed())
        return;

    addVelocityY(owner->game->getGravity() * deltaTime);
}