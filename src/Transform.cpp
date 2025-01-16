#include "Game.hpp"
#include "Transform.hpp"

struct Vector;

Transform::Transform(Vector position, Vector velocity, Vector size) : position(position), velocity(velocity), size(size) {}

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
        position.y = worldHeight - (size.y / 2);

        if (velocity.y > 0)
        {
            velocity.y = 0;
        }

        return;
    }

    if (velocity.y >= Game::maxFallSpeed)
    {
        return;
    }

    velocity.y += gravity * deltaTime;
}