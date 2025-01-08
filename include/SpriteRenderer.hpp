#pragma once
#include <SDL2/SDL.h>
#include "Component.hpp"

struct Vector;
class GameObject;
class ResourceManager;

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(GameObject *owner, ResourceManager &resourceManager, const std::string &textureFilePath);

    void render(SDL_Renderer *renderer, Vector pos, Vector size, bool flipLeft = false);

protected:
    SDL_Texture *texture;
};