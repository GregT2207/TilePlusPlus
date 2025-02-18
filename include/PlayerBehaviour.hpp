#pragma once
#include "Component.hpp"

class Vector;

class PlayerBehaviour : public Component
{
public:
    PlayerBehaviour() {};

    void handleEvents(SDL_Event &event) override;

protected:
    void jump();
    void checkTileActions(SDL_Event &event);
    void destroyTile(Vector mousePos);
    void placeTile(Vector mousePos);

    const int movementSpeed = 300;
    const int jumpPower = 800;
};