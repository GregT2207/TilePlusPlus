#pragma once
#include <SDL2/SDL.h>
#include "Component.hpp"

class ResourceManager;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(ResourceManager *resourceManager, const std::string &textureFilePath);

    void render(SDL_Renderer *renderer);

protected:
    SDL_Texture *texture;
};