#pragma once
#include "Component.hpp"

class MovementBehaviour : public Component
{
public:
    MovementBehaviour() {};

    void jump();

protected:
    const int jumpPower = 800;
};