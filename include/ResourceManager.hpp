#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Renderer.hpp"

class Renderer;

class ResourceManager
{
public:
    ResourceManager(Renderer *renderer);

    bool init();

    SDL_Texture *loadTexture(const std::string &filePath);

private:
    Renderer *renderer;
};