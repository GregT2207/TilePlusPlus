#pragma once
#include "Component.hpp"

class EnemyBehaviour : public Component
{
public:
    EnemyBehaviour(GameObject *player) : player(player) {};

    void update(float deltaTime) override;

private:
    void followPlayer();

    GameObject *player;
};