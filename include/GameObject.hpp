#pragma once
#include <SDL2/SDL.h>
#include <string>

class GameObject
{
public:
    GameObject(SDL_Renderer *renderer, std::string name, int x, int y, SDL_Color color);
    ~GameObject();

    void update(unsigned int deltaTime, int worldWidth, int worldHeight, int gravity);
    void render();

    int x;
    int y;
    int width;
    int height;
    SDL_Color color;

private:
    void applyGravity(unsigned int deltaTime, int gravity, int worldHeight);

    SDL_Renderer *renderer;
    std::string name;
};