#pragma once
#include <string>
#include <vector>
#include "Game.hpp"
#include "components/Component.hpp"
#include "geometry/Transform.hpp"
#include "components/Collider.hpp"
#include "components/Health.hpp"
#include "components/Renderer.hpp"
#include "components/PlayerBehaviour.hpp"
#include "components/EnemyBehaviour.hpp"
#include "components/MovementBehaviour.hpp"
#include "components/Inventory.hpp"
#include "components/AttackBehaviour.hpp"

class GameObject
{
public:
    GameObject(Game *game, std::string name);
    virtual ~GameObject();

    virtual void init();
    virtual void handleEvents(SDL_Event &event);
    virtual void update(float deltaTime);
    void render(SDL_Renderer *renderer);

    std::string getName() const { return name; }

    template <typename T, typename... Args>
    T *addComponent(Args &&...args)
    {
        T *comp = new T(std::forward<Args>(args)...);
        comp->owner = this;
        components.push_back(comp);

        if constexpr (std::is_same_v<T, Collider>)
        {
            game->colliders.push_back(comp);
        }
        else if constexpr (std::is_same_v<T, Camera>)
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