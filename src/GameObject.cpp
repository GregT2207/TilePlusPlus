#include "GameObject.hpp"
#include "Game.hpp"
#include "string"

GameObject::GameObject(SDL_Renderer *renderer, std::string name, int x, int y)
    : renderer(renderer), name(name), x(x), y(y)
{
    this->width = 50;
    this->height = 100;
}

GameObject::~GameObject()
{
}

void GameObject::handleEvents(SDL_Event event) {};

void GameObject::update(float deltaTime, int worldWidth, int worldHeight, int gravity)
{
    updatePosition(deltaTime);
    applyGravity(deltaTime, gravity, worldHeight);
}

void GameObject::updatePosition(float deltaTime)
{
    x += velocity.x * deltaTime;
    y += velocity.y * deltaTime;
}

void GameObject::applyGravity(float deltaTime, int gravity, int worldHeight)
{
    if ((y + height / 2) >= worldHeight)
    {
        velocity.y = 0;
        y = worldHeight - (height / 2);
        return;
    }

    if (velocity.y >= Game::maxFallSpeed)
    {
        return;
    }

    velocity.y += gravity * deltaTime;
}

void GameObject::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_Rect sprite = {x - (width / 2), y - (height / 2), width, height};
    SDL_RenderFillRect(renderer, &sprite);
}