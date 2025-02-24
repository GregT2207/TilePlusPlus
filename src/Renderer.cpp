#include <iostream>
#include "Renderer.hpp"

Renderer::Renderer(SDL_Window *window)
{
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
    }
}

int Renderer::setRenderDrawColor(
    Uint8 r, Uint8 g, Uint8 b,
    Uint8 a)
{
    return SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);
}

void Renderer::renderPresent()
{
    return SDL_RenderPresent(sdlRenderer);
}

int Renderer::renderClear()
{
    return SDL_RenderClear(sdlRenderer);
}

int Renderer::renderDrawRect(const SDL_Rect *rect)
{
    return SDL_RenderDrawRect(sdlRenderer, rect);
}

int Renderer::renderCopy(
    SDL_Texture *texture,
    const SDL_Rect *srcRect,
    const SDL_Rect *destRect)
{
    return SDL_RenderCopy(sdlRenderer, texture, srcRect, destRect);
}

int Renderer::renderCopyEx(
    SDL_Texture *texture,
    const SDL_Rect *srcRect,
    const SDL_Rect *destRect,
    const double angle,
    const SDL_Point *center,
    const SDL_RendererFlip flip)
{
    return SDL_RenderCopyEx(sdlRenderer, texture, srcRect, destRect, angle, center, flip);
}

int Renderer::drawString(int x, int y, const char *s)
{
    return SDLTest_DrawString(sdlRenderer, x, y, s);
}