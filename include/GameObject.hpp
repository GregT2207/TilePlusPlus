#pragma once
#include <SDL2/SDL.h>
#include <string>

class GameObject
{
public:
    GameObject(SDL_Renderer *renderer, std::string name, int x, int y);
    ~GameObject();

    void handleEvents(SDL_Event event);
    void update(float deltaTime, int worldWidth, int worldHeight, int gravity);
    void render();

    int getX() const { return x; }
    int getY() const { return y; }

protected:
    struct Velocity
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    Velocity velocity;

private:
    void updatePosition(float deltaTime);
    void applyGravity(float deltaTime, int gravity, int worldHeight);

    SDL_Renderer *renderer;
    std::string name;

    int width;
    int height;
    int x;
    int y;
};