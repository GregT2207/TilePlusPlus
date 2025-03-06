#include "Health.hpp"

int Health::hurt(int amount)
{
    hp -= amount;
}

int Health::heal(int amount)
{
    hp += amount;
}