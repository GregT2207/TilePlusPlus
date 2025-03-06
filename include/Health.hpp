#pragma once
#include "Component.hpp"

class Health : public Component
{
public:
    Health(int hp = 100) : hp(hp) {};

    int hurt(int amount);
    int heal(int amount);

    int getHp() const { return hp; }

private:
    int hp;
};