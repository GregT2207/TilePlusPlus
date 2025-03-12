#include "geometry/Transform.hpp"

Transform::Transform(Vector position, Vector velocity, Vector size) : position(position), velocity(velocity), size(size) {}

void Transform::update(float deltaTime)
{
    addPosition(velocity * deltaTime);

    applyGravity(deltaTime);
    applyDrag(deltaTime);

    if (velocity.magnitude() < 1.0f)
        velocity = {0, 0};
}

void Transform::applyGravity(float deltaTime)
{
    if (velocity.y >= owner->game->getPhysicsManager()->maxFallSpeed)
        return;

    addVelocityY(owner->game->getPhysicsManager()->gravity * deltaTime);
}

void Transform::applyDrag(float deltaTime)
{
    Collider *collider = owner->getComponent<Collider>();
    int drag = collider && collider->isGrounded() ? owner->game->getPhysicsManager()->groundResistance : owner->game->getPhysicsManager()->airResistance;

    velocity -= velocity * drag * deltaTime;
}