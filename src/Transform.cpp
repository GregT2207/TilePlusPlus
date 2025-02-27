#include "Game.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

Transform::Transform(Vector position, Vector velocity, Vector size) : position(position), velocity(velocity), size(size) {}

void Transform::update(float deltaTime)
{
    if (SDL_GetTicks64() >= 4000)
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