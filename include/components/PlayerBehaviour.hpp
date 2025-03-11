#pragma once
#include "components/Component.hpp"
#include "enums/Tile.hpp"

class Vector;

class PlayerBehaviour : public Component
{
public:
    PlayerBehaviour() {};

    void handleEvents(SDL_Event &event) override;
    void update(float deltaTime) override;

protected:
    Vector getClickedWorldPos();
    void useItem();
    void placeTile(Vector mousePos, Tile tile);

    const int keyboardMovementSpeed = 300;
    float movementVelocity = 0.0f;
    bool jumping = false;
};