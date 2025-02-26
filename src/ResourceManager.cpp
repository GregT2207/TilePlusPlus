#include "ResourceManager.hpp"

ResourceManager::ResourceManager(SDL_Renderer *renderer) : renderer(renderer) {}

bool ResourceManager::init()
{
    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        return false;
    }

    return true;
}

SDL_Texture *ResourceManager::loadTexture(const std::string &filePath)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, ("../assets/" + filePath).c_str());
    return texture;
}