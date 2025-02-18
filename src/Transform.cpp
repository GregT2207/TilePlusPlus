#include "Game.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"

Transform::Transform(Vector position, Vector velocity, Vector size) : position(position), velocity(velocity), size(size) {}

void Transform::update(float deltaTime, int gravity, int worldHeight)
{
    if (SDL_GetTicks64() >= 3000)
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