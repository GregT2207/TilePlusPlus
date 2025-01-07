#pragma once
#include <SDL2/SDL.h>
#include "Component.hpp"

struct Vector;
class GameObject;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(GameObject *owner);

    void render(SDL_Renderer *renderer, Vector pos);

protected:
    SDL_Color sprite;
};