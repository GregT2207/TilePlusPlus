#include "SpriteRenderer.hpp"
#include "GameObject.hpp"

struct Vector;

SpriteRenderer::SpriteRenderer(GameObject *owner) : Component(owner) {};

void SpriteRenderer::render(SDL_Renderer *renderer, Vector pos, Vector size)
{
    SDL_SetRenderDrawColor(renderer, 255, 170, 169, 255);
    SDL_Rect rect = {static_cast<int>(pos.x - (size.x / 2)), static_cast<int>(pos.y - (size.y / 2)), static_cast<int>(size.x), static_cast<int>(size.y)};
    SDL_RenderFillRect(renderer, &rect);
}