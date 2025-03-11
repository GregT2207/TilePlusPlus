#pragma once
#include <SDL2/SDL.h>
#include "Component.hpp"
#include "Vector.hpp"

class ResourceManager;
class Camera;
class Transform;
struct RenderParams
{
    Vector pos;
    Vector size;
    Vector dir;
    float left;
    float right;
    float top;
    float bottom;
};

class Renderer : public Component
{
public:
    Renderer(SDL_Renderer *renderer, ResourceManager *resourceManager, const std::string &textureFilePath);

    void render(SDL_Renderer *renderer);
    RenderParams getRenderParams(Transform *transform) const;
    void renderMainSprite(Camera *camera, Transform *transform);
    void renderInventoryItem(Camera *camera, Transform *transform);
    void renderHealthBar(Camera *camera, Transform *transform);
    void renderNameTag(Camera *camera, Transform *transform);

protected:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
};