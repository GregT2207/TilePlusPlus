#include <GameObject.hpp>
#include <string>

GameObject::GameObject(SDL_Renderer *renderer, std::string name, int x, int y, SDL_Color color)
    : renderer(renderer), name(name), x(x), y(y), color(color)
{
    this->width = 100;
    this->height = 100;
}

GameObject::~GameObject()
{
}

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
    if ((y + height / 2) < worldHeight)
    {
        velocity.y += gravity * deltaTime;
    }
    else
    {
        velocity.y = 0;
        y = worldHeight - (height / 2);
    }
}

void GameObject::render()
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect sprite = {x - (width / 2), y - (height / 2), width, height};
    SDL_RenderFillRect(renderer, &sprite);
}