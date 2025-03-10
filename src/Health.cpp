#include "Health.hpp"

int Health::hurt(int amount)
{
    hp -= amount;
    return hp;
}

int Health::hurtKnockback(int hurtAmount, int knockbackAmount, Vector direction)
{
    int newHp = hurt(hurtAmount);

    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return newHp;

    transform->addVelocity(direction * knockbackAmount);
    return newHp;
}

int Health::heal(int amount)
{
    hp += amount;
    return hp;
}