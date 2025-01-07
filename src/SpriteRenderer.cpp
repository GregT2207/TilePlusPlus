#include "SpriteRenderer.hpp"
#include "GameObject.hpp"

struct Vector;

SpriteRenderer::SpriteRenderer(GameObject *owner) : Component(owner) {};

void SpriteRenderer::render(SDL_Renderer *renderer, Vector pos)
{
    SDL_SetRenderDrawColor(renderer, 0, 180, 50, 255);
    SDL_Rect rect = {static_cast<int>(pos.x), static_cast<int>(pos.y), 50, 100};
    SDL_RenderFillRect(renderer, &rect);
}