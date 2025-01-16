#pragma once
#include <SDL2/SDL.h>

class GameObject;

class Component
{
public:
    Component() {};
    virtual ~Component() = 0;

    virtual void update(float deltaTime, int gravity, int worldHeight) {}
    virtual void render(SDL_Renderer *renderer) {}

    GameObject *owner;
};