#include "string"
#include "GameObject.hpp"
#include "Game.hpp"

GameObject::GameObject(std::string name) : name(name) {}
GameObject::~GameObject() {}

void GameObject::init() {};

void GameObject::handleEvents(SDL_Event &event) {};

void GameObject::update(float deltaTime, int worldWidth, int worldHeight, int gravity)
{
    for (auto &component : components)
    {
        component->update(deltaTime, gravity, worldHeight);
    }
}

void GameObject::render(SDL_Renderer *renderer)
{
    for (auto &component : components)
    {
        component->render(renderer);
    }
}