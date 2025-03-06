#include "Health.hpp"

int Health::hurt(int amount)
{
    hp -= amount;
    return hp;
}

int Health::heal(int amount)
{
    hp += amount;
    return hp;
}