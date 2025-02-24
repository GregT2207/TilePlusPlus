#include "string"
#include "GameObject.hpp"

GameObject::GameObject(Game *game, std::string name) : game(game), name(name) {}
GameObject::~GameObject() {}

void GameObject::init() {};

void GameObject::handleEvents(SDL_Event &event)
{
    for (auto component : components)
    {
        component->handleEvents(event);
    }
};

void GameObject::update(float deltaTime)
{
    for (auto component : components)
    {
        component->update(deltaTime);
    }
}

void GameObject::render()
{
    for (auto component : components)
    {
        component->render();
    }
}