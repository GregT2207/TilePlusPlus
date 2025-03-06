#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test.h>
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "Camera.hpp"

struct Vector;

Renderer::Renderer(SDL_Renderer *renderer, ResourceManager *resourceManager, const std::string &textureFilePath) : renderer(renderer)
{
    texture = resourceManager->loadTexture(textureFilePath);
}

void Renderer::render(SDL_Renderer *renderer)
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return;

    for (Camera *camera : owner->game->cameras)
    {
        renderMainSprite(camera, transform);
        renderInventoryItem(camera, transform);
        renderNameTag(camera, transform);
    }
}

void Renderer::renderMainSprite(Camera *camera, Transform *transform)
{
    Vector pos = transform->getPosition();
    Vector size = transform->getSize();
    Vector dir = transform->getDirection();

    float left = pos.x - (size.x / 2);
    float top = pos.y - (size.y / 2);

    SDL_Rect dest = camera->worldRectToScreenRect({left, top, size.x, size.y});
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, dir.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Renderer::renderInventoryItem(Camera *camera, Transform *transform)
{
    Inventory *inv = owner->getComponent<Inventory>();
    if (!inv)
        return;

    Item *item = inv->getActiveItem();
    if (!item)
        return;

    Vector pos = transform->getPosition();
    Vector size = transform->getSize();
    Vector dir = transform->getDirection();

    float textureLength = item->getTile() ? size.x * 0.35f : size.x * 0.75f;
    float textureOffset = 0.1f;
    SDL_Rect destRect = camera->worldRectToScreenRect({dir.x > 0 ? pos.x + (size.x * textureOffset) : pos.x - (size.x * textureOffset) - textureLength,
                                                       pos.y - (textureLength / 2),
                                                       textureLength,
                                                       textureLength});
    SDL_RenderCopyEx(renderer, item->getTexture(), nullptr, &destRect, item->getTile() ? 40 * (dir.x > 0 ? 1 : -1) : 0, nullptr, dir.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Renderer::renderNameTag(Camera *camera, Transform *transform)
{
    std::string label = owner->getName();
    const int approxCharWidth = 8;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    Vector stringPoint = camera->worldPosToScreenPos({transform->getPosition().x - (label.size() * approxCharWidth / camera->getZoom() / 2), transform->getPosition().y - (transform->getSize().y / 2) - 20});
    SDLTest_DrawString(renderer, stringPoint.x, stringPoint.y, label.c_str());
}