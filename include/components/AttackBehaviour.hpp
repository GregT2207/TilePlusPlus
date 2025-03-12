#pragma once
#include "components/Component.hpp"

class AttackBehaviour : public Component
{
public:
    AttackBehaviour(int damage, int knockback, int cooldown, int reach = 0, int scoop = 0) : damage(damage), knockback(knockback), cooldown(cooldown), reach(reach), scoop(scoop) {};
    void update(float deltaTime) override;
    bool attack(GameObject *other);

private:
    int damage;
    int knockback;
    int cooldown;
    int reach;
    int scoop;

    float timeSinceAttack = 0.0f;
};