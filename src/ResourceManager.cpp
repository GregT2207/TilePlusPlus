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
    std::string fullFilePath = ("../assets/" + filePath);
    SDL_Texture *texture = IMG_LoadTexture(renderer, fullFilePath.c_str());
    if (!texture)
    {
        SDL_Log("File %s not found", fullFilePath.c_str());
    }

    return texture;
}