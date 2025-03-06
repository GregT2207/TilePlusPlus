#pragma once
#include "Component.hpp"

class Health : public Component
{
public:
    Health(int maxHp = 100, int initialHp = 0) : hp(initialHp > 0 ? initialHp : maxHp), maxHp(maxHp) {};

    int hurt(int amount);
    int heal(int amount);

    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }

private:
    int hp;
    int maxHp;
};