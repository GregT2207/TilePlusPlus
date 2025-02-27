#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test.h>
#include "SpriteRenderer.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "Camera.hpp"

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

    float left = pos.x - (size.x / 2);
    float top = pos.y - (size.y / 2);

    for (Camera *camera : owner->game->cameras)
    {
        SDL_Rect dest = camera->worldRectToScreenRect({left, top, size.x, size.y});
        SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, dir.x > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

        std::string label = owner->getName();
        const int approxCharWidth = 8;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        Vector stringPoint = camera->worldPosToScreenPos({pos.x - (label.size() * approxCharWidth / 2), pos.y - (size.y / 2) - 20});
        SDLTest_DrawString(renderer, stringPoint.x, stringPoint.y, label.c_str());
    }
}