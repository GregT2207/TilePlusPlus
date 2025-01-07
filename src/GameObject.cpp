#include "string"
#include "GameObject.hpp"
#include "Game.hpp"

GameObject::GameObject(std::string name) : name(name), transform(nullptr), spriteRenderer(nullptr) {}
GameObject::~GameObject() {}

void GameObject::init() {};

void GameObject::handleEvents(SDL_Event &event) {};

void GameObject::update(float deltaTime, int worldWidth, int worldHeight, int gravity)
{
    if (transform)
    {
        transform->update(deltaTime);
    }
}

void GameObject::render(SDL_Renderer *renderer)
{
    if (spriteRenderer)
    {
        spriteRenderer->render(renderer, transform->getPosition());
    }
}