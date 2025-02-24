#include <iostream>
#include "Renderer.hpp"

Renderer::Renderer(Game *game, SDL_Window *window) : game(game)
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

int Renderer::renderDrawRect(SDL_Rect rect)
{
    SDL_Rect offsetRect = game->getCamera()->getWorldPos(rect);
    return SDL_RenderDrawRect(sdlRenderer, &offsetRect);
}

int Renderer::renderCopy(SDL_Texture *texture,
                         SDL_Rect srcRect,
                         SDL_Rect destRect)
{
    SDL_Rect *srcRectPtr = srcRect.w == -1 && srcRect.h == -1 ? nullptr : &srcRect;
    SDL_Rect *offsetDestRectPtr = nullptr;
    if (destRect.w != -1 && destRect.h != -1)
    {
        SDL_Rect offsetDestRect = game->getCamera()->getWorldPos(destRect);
        offsetDestRectPtr = &offsetDestRect;
    }

    return SDL_RenderCopy(sdlRenderer, texture, srcRectPtr, offsetDestRectPtr);
}

int Renderer::renderCopyEx(SDL_Texture *texture,
                           SDL_Rect srcRect,
                           SDL_Rect destRect,
                           const double angle,
                           const SDL_Point *center,
                           const SDL_RendererFlip flip)
{
    SDL_Rect *srcRectPtr = srcRect.w == -1 && srcRect.h == -1 ? nullptr : &srcRect;
    SDL_Rect *offsetDestRectPtr = nullptr;
    if (destRect.w != -1 && destRect.h != -1)
    {
        SDL_Rect offsetDestRect = game->getCamera()->getWorldPos(destRect);
        offsetDestRectPtr = &offsetDestRect;
    }

    return SDL_RenderCopyEx(sdlRenderer, texture, srcRectPtr, offsetDestRectPtr, angle, center, flip);
}

int Renderer::drawString(int x, int y, const char *s)
{
    Vector offsetPos = game->getCamera()->getWorldPos(Vector({x, y}));
    return SDLTest_DrawString(sdlRenderer, offsetPos.x, offsetPos.y, s);
}