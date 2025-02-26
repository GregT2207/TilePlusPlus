#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class ResourceManager
{
public:
    ResourceManager(SDL_Renderer *renderer);

    bool init();

    SDL_Texture *loadTexture(const std::string &filePath);

private:
    SDL_Renderer *renderer;
};