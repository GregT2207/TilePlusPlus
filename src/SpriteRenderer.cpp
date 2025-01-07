#include <SDL2/SDL_test.h>
#include "SpriteRenderer.hpp"
#include "GameObject.hpp"

struct Vector;

SpriteRenderer::SpriteRenderer(GameObject *owner) : Component(owner) {};

void SpriteRenderer::render(SDL_Renderer *renderer, Vector pos, Vector size)
{
    int left = static_cast<int>(pos.x - (size.x / 2));
    int top = static_cast<int>(pos.y - (size.y / 2));

    SDL_SetRenderDrawColor(renderer, 255, 170, 169, 255);
    SDL_Rect rect = {left, top, static_cast<int>(size.x), static_cast<int>(size.y)};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDLTest_DrawString(renderer, left + 10, top - 20, owner->getName().c_str());
}