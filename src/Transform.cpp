#include "Game.hpp"
#include "Transform.hpp"

struct Vector;

Transform::Transform(GameObject *owner, Vector position, Vector velocity, Vector size)
    : Component(owner), position(position), velocity(velocity), size(size) {};

void Transform::update(float deltaTime, int gravity, int worldHeight)
{
    applyGravity(deltaTime, gravity, worldHeight);

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Transform::applyGravity(float deltaTime, int gravity, int worldHeight)
{
    if ((position.y + size.y / 2) >= worldHeight)
    {
        velocity.y = 0;
        position.y = worldHeight - (size.y / 2);
        return;
    }

    if (velocity.y >= Game::maxFallSpeed)
    {
        return;
    }

    velocity.y += gravity * deltaTime;
}