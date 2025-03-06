#pragma once
#include <string>
#include <vector>
#include "Game.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "Collider.hpp"
#include "Health.hpp"
#include "Renderer.hpp"
#include "PlayerBehaviour.hpp"
#include "EnemyBehaviour.hpp"
#include "MovementBehaviour.hpp"
#include "Inventory.hpp"

using namespace std;

class GameObject
{
public:
    GameObject(Game *game, string name);
    ~GameObject();

    virtual void init();
    virtual void handleEvents(SDL_Event &event);
    virtual void update(float deltaTime);
    void render(SDL_Renderer *renderer);

    string getName() const { return name; }

    template <typename T, typename... Args>
    T *addComponent(Args &&...args)
    {
        T *comp = new T(std::forward<Args>(args)...);
        comp->owner = this;
        components.push_back(comp);

        if constexpr (is_same_v<T, Collider>)
        {
            game->colliders.push_back(comp);
        }
        else if constexpr (is_same_v<T, Camera>)
        {
            game->cameras.push_back(comp);
        }

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