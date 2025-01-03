#include <GameObject.hpp>

GameObject::GameObject(SDL_Renderer *renderer, int x, int y)
{
    this->renderer = renderer;
    this->x = x;
    this->y = y;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
}

void GameObject::render()
{
    SDL_Rect sprite = {x, y, 10, 10};
    SDL_RenderFillRect(renderer, &sprite);
}