#pragma once
#include <SDL2/SDL.h>

class GameObject;

class Component
{
public:
    Component() {};
    virtual ~Component() = 0;

    virtual void handleEvents(SDL_Event &event) {}
    virtual void update(float deltaTime) {}
    virtual void render(SDL_Renderer *renderer) {}

    GameObject *owner;
};