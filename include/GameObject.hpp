#pragma once
#include <string>
#include <vector>
#include "Game.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include "SpriteRenderer.hpp"

class GameObject
{
public:
    GameObject(Game *game, std::string name);
    ~GameObject();

    void virtual init();
    void virtual handleEvents(SDL_Event &event);
    void virtual update(float deltaTime, int worldWidth, int worldHeight, int gravity);
    void render(SDL_Renderer *renderer);

    std::string getName() const { return name; }

    template <typename T, typename... Args>
    T *addComponent(Args &&...args)
    {
        T *comp = new T(std::forward<Args>(args)...);
        comp->owner = this;
        components.push_back(comp);
        return comp;
    }

    template <typename T>
    T *getComponent()
    {
        for (auto comp : components)
        {
            if (T *casted = dynamic_cast<T *>(comp))
            {
                return casted;
            }
        }
        return nullptr;
    }

    Game *game;

protected:
    std::string name;

private:
    std::vector<Component *> components;
};