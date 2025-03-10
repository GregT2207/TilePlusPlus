#include "Health.hpp"

int Health::hurt(int amount)
{
    hp = std::max(hp - amount, 0);

    if (hp <= 0)
        die();

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
    hp = std::min(hp + amount, maxHp);
    return hp;
}

void Health::die()
{
    Transform *transform = owner->getComponent<Transform>();
    if (transform)
    {
        transform->setPosition({0.0f, 0.0f});
        transform->setVelocity({0.0f, 0.0f});
        transform->setDirection({1.0f, 1.0f});
    }

    hp = maxHp;
}