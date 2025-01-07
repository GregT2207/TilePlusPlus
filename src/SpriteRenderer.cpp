#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test.h>
#include "SpriteRenderer.hpp"
#include "GameObject.hpp"

struct Vector;

SpriteRenderer::SpriteRenderer(GameObject *owner, SDL_Renderer *renderer, std::string textureFilePath) : Component(owner)
{
    textureFilePath = "../assets/" + textureFilePath;

    SDL_Surface *surface = IMG_Load(textureFilePath.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load texture: " << textureFilePath << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void SpriteRenderer::render(SDL_Renderer *renderer, Vector pos, Vector size)
{
    int left = static_cast<int>(pos.x - (size.x / 2));
    int top = static_cast<int>(pos.y - (size.y / 2));

    SDL_Rect dest = {left, top, static_cast<int>(size.x), static_cast<int>(size.y)};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDLTest_DrawString(renderer, left + 10, top - 20, owner->getName().c_str());
}