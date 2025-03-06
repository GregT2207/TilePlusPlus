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
        renderHealthBar(camera, transform);
        renderNameTag(camera, transform);
    }
}

RenderParams Renderer::getRenderParams(Transform *transform) const
{
    Vector pos = transform->getPosition();
    Vector size = transform->getSize();
    Vector dir = transform->getDirection();

    float left = pos.x - (size.x / 2);
    float right = pos.x + (size.x / 2);
    float top = pos.y - (size.y / 2);
    float bottom = pos.y + (size.y / 2);

    return {pos, size, dir, left, right, top, bottom};
}

void Renderer::renderMainSprite(Camera *camera, Transform *transform)
{
    RenderParams rp = getRenderParams(transform);

    SDL_Rect dest = camera->worldRectToScreenRect({rp.left, rp.top, rp.size.x, rp.size.y});
    SDL_RenderCopyEx(renderer, texture, nullptr, &dest, 0, nullptr, rp.dir.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Renderer::renderInventoryItem(Camera *camera, Transform *transform)
{
    Inventory *inv = owner->getComponent<Inventory>();
    if (!inv)
        return;

    Item *item = inv->getActiveItem();
    if (!item)
        return;

    RenderParams rp = getRenderParams(transform);

    float textureLength = item->getTile() ? rp.size.x * 0.35f : rp.size.x * 0.75f;
    float textureOffset = 0.1f;
    SDL_Rect destRect = camera->worldRectToScreenRect({rp.dir.x > 0 ? rp.pos.x + (rp.size.x * textureOffset) : rp.pos.x - (rp.size.x * textureOffset) - textureLength,
                                                       rp.pos.y - (textureLength / 2),
                                                       textureLength,
                                                       textureLength});
    SDL_RenderCopyEx(renderer, item->getTexture(), nullptr, &destRect, item->getTile() ? 40 * (rp.dir.x > 0 ? 1 : -1) : 0, nullptr, rp.dir.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}

void Renderer::renderHealthBar(Camera *camera, Transform *transform)
{
    Health *health = owner->getComponent<Health>();
    if (!health)
        return;

    RenderParams rp = getRenderParams(transform);

    const int singleHpWidth = 1;
    const int barMargin = 3;
    const int barHeight = 15;

    int healthBarWidth = health->getHp() * singleHpWidth;
    int maxBarWidth = health->getMaxHp() * singleHpWidth;

    BoundingBox healthBar = {(int)rp.pos.x - (maxBarWidth / 2) - barMargin, (int)rp.top - 30 - barHeight, healthBarWidth, barHeight};
    BoundingBox maxBar = {(int)healthBar.x - barMargin, (int)healthBar.y - barMargin, maxBarWidth + (barMargin * 2), (int)healthBar.h + (barMargin * 2)};

    SDL_Rect maxBarRect = camera->worldRectToScreenRect(maxBar);
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &maxBarRect);

    SDL_Rect healthBarRect = camera->worldRectToScreenRect(healthBar);
    SDL_SetRenderDrawColor(renderer, 255, 0, 50, 255);
    SDL_RenderFillRect(renderer, &healthBarRect);
}

void Renderer::renderNameTag(Camera *camera, Transform *transform)
{
    RenderParams rp = getRenderParams(transform);

    std::string label = owner->getName();
    const int approxCharWidth = 8;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    Vector stringPoint = camera->worldPosToScreenPos({rp.pos.x - (label.size() * approxCharWidth / camera->getZoom() / 2), rp.top - 15});
    SDLTest_DrawString(renderer, stringPoint.x, stringPoint.y, label.c_str());
}