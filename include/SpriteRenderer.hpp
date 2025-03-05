#pragma once
#include <SDL2/SDL.h>
#include "Component.hpp"

class ResourceManager;
class Camera;
class Transform;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(SDL_Renderer *renderer, ResourceManager *resourceManager, const std::string &textureFilePath);

    void render(SDL_Renderer *renderer);
    void renderMainSprite(Camera *camera, Transform *transform);
    void renderInventoryItem(Camera *camera, Transform *transform);
    void renderNameTag(Camera *camera, Transform *transform);

protected:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
};