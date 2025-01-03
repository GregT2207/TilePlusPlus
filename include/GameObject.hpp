#pragma once
#include <SDL2/SDL.h>

class GameObject
{
public:
    GameObject(SDL_Renderer *renderer, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    SDL_Renderer *renderer;
    int x;
    int y;
};