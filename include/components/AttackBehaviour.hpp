#pragma once
#include "components/Component.hpp"

class AttackBehaviour : public Component
{
public:
    void update(float deltaTime) override;
    bool attack(GameObject *other);

private:
    const int reach = 50;
    const int damage = 5;
    const int knockback = 600;
    const int scoop = 1;
    const int cooldown = 2;

    float timeSinceAttack = 0.0f;
};