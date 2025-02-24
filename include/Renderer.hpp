#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_test.h>
#include "Game.hpp"

class Game;

class Renderer
{
public:
    Renderer(Game *game, SDL_Window *window);

    SDL_Renderer *getSDLRenderer() const { return sdlRenderer; }

    int setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b,
                           Uint8 a);
    void renderPresent();
    int renderClear();
    int renderDrawRect(SDL_Rect rect, bool fixed = false);
    int renderCopy(SDL_Texture *texture,
                   SDL_Rect srcRect,
                   SDL_Rect dstRect,
                   bool fixed = false);
    int renderCopyEx(SDL_Texture *texture,
                     SDL_Rect srcRect,
                     SDL_Rect dstRect,
                     const double angle,
                     const SDL_Point *center,
                     const SDL_RendererFlip flip,
                     bool fixed = false);
    int drawString(int x, int y, const char *s, bool fixed = false);

private:
    Game *game;
    SDL_Renderer *sdlRenderer;
};