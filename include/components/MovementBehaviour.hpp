#pragma once
#include "components/Component.hpp"

class MovementBehaviour : public Component
{
public:
    MovementBehaviour(float canJump = true) : canJump(canJump) {};

    void jump();

protected:
    const int jumpPower = 800;
    float canJump;
};