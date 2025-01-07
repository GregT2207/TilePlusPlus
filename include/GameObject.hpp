#pragma once
#include <string>
#include "Transform.hpp"
#include "SpriteRenderer.hpp"

class GameObject
{
public:
    GameObject(std::string name);
    ~GameObject();

    void virtual init();
    void virtual handleEvents(SDL_Event &event);
    void virtual update(float deltaTime, int worldWidth, int worldHeight, int gravity);
    void render(SDL_Renderer *renderer);

    std::string getName() const { return name; }

    Transform *transform;
    SpriteRenderer *spriteRenderer;

protected:
    std::string name;
};