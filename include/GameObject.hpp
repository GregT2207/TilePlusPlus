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
    int getX() const { return x; }
    int getY() const { return y; }
    void setVelocity(float vx, float vy)
    {
        velocity.x = vx;
        velocity.y = vy;
    }

    int width;
    int height;
    SDL_Color color;

private:
    void applyGravity(unsigned int deltaTime, int gravity, int worldHeight);

    SDL_Renderer *renderer;
    std::string name;

    int x;
    int y;

    struct Velocity
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    Velocity velocity;
};