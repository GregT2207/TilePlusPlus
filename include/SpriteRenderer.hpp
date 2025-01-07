#pragma once
#include <SDL2/SDL.h>
#include "Component.hpp"

struct Vector;
class GameObject;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(GameObject *owner, SDL_Renderer *renderer, std::string textureFilePath);

    void render(SDL_Renderer *renderer, Vector pos, Vector size, bool flipLeft = false);

protected:
    SDL_Texture *texture;
};