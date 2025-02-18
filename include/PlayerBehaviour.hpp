#pragma once
#include "Component.hpp"

class PlayerBehaviour : public Component
{
public:
    PlayerBehaviour() {};

    void handleEvents(SDL_Event &event) override;

protected:
    void jump();
    void destroyTile();
    void placeTile();

    const int movementSpeed = 300;
    const int jumpPower = 800;
};