#pragma once
#include "Component.hpp"

class Vector;

class PlayerBehaviour : public Component
{
public:
    PlayerBehaviour() {};

    void handleEvents(SDL_Event &event) override;
    void update(float deltaTime) override;

protected:
    void checkTileActions(SDL_Event &event);
    void destroyTile(Vector mousePos);
    void placeTile(Vector mousePos);

    const int keyboardMovementSpeed = 300;
    float movementVelocity = 0.0f;
};