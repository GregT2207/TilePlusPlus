#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test.h>
#include "SpriteRenderer.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"

struct Vector;

SpriteRenderer::SpriteRenderer(GameObject *owner, ResourceManager &resourceManager, const std::string &textureFilePath) : Component(owner)
{
    texture = resourceManager.loadTexture(textureFilePath);
    if (!texture)
    {
        std::cerr << "Failed to load texture: " << textureFilePath << std::endl;
    }
}

void SpriteRenderer::render(SDL_Renderer *renderer, Vector pos, Vector size, bool flipLeft)
{
    int left = static_cast<int>(pos.x - (size.x / 2));
    int top = static_cast<int>(pos.y - (size.y / 2));

    SDL_Rect dest = {left, top, static_cast<int>(size.x), static_cast<int>(size.y)};
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, flipLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDLTest_DrawString(renderer, left + 10, top - 20, owner->getName().c_str());
}