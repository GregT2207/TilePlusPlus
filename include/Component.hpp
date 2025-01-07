#pragma once
#include <SDL2/SDL.h>

class GameObject;

class Component
{
public:
    Component(GameObject *owner) : owner(owner) {};
    virtual ~Component() = 0;

    GameObject *getOwner() const { return owner; }

protected:
    GameObject *owner;
};