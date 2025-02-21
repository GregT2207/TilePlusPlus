#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test.h>
#include "SpriteRenderer.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"

struct Vector;

SpriteRenderer::SpriteRenderer(ResourceManager &resourceManager, const std::string &textureFilePath)
{
    texture = resourceManager.loadTexture(textureFilePath);
    if (!texture)
    {
        std::cerr << "Failed to load texture: " << textureFilePath << std::endl;
    }
}

void SpriteRenderer::render(SDL_Renderer *renderer)
{
    Transform *transform = owner->getComponent<Transform>();
    Vector pos = transform->getPosition();
    Vector size = transform->getSize();
    Vector dir = transform->getDirection();

    int left = static_cast<int>(pos.x - (size.x / 2));
    int top = static_cast<int>(pos.y - (size.y / 2));

    SDL_Rect dest = owner->game->getCamera()->getWorldPos({left, top, static_cast<int>(size.x), static_cast<int>(size.y)});
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, dir.x > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

    std::string label = owner->getName();
    const int approxCharWidth = 8;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect stringRect = owner->game->getCamera()->getWorldPos({static_cast<int>(pos.x - (label.size() * approxCharWidth / 2)), top - 20, 0, 0});
    SDLTest_DrawString(renderer, stringRect.x, stringRect.y, label.c_str());
}