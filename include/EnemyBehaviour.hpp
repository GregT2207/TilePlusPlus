#pragma once
#include "Component.hpp"

class EnemyBehaviour : public Component
{
public:
    EnemyBehaviour(GameObject *player) : player(player) {};

    void update(float deltaTime) override;

private:
    void followPlayer();
    bool attackPlayer();

    const int reach = 10;
    const int damage = 5;
    const int knockback = 1000;
    const int scoop = 1;
    const int cooldown = 2;
    float timeSinceAttack = 0;
    GameObject *player;
};