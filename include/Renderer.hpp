#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_test.h>

class Renderer
{
public:
    Renderer(SDL_Window *window);

    SDL_Renderer *getSDLRenderer() const { return sdlRenderer; }

    int setRenderDrawColor(Uint8 r, Uint8 g, Uint8 b,
                           Uint8 a);
    void renderPresent();
    int renderClear();
    int renderDrawRect(const SDL_Rect *rect);
    int renderCopy(
        SDL_Texture *texture,
        const SDL_Rect *srcrect,
        const SDL_Rect *dstrect);
    int renderCopyEx(SDL_Texture *texture,
                     const SDL_Rect *srcrect,
                     const SDL_Rect *dstrect,
                     const double angle,
                     const SDL_Point *center,
                     const SDL_RendererFlip flip);
    int drawString(int x, int y, const char *s);

private:
    SDL_Renderer *sdlRenderer;
};