#include "components/AttackBehaviour.hpp"
#include "GameObject.hpp"

void AttackBehaviour::update(float deltaTime)
{
    timeSinceAttack += deltaTime;
}

bool AttackBehaviour::attack(GameObject *other)
{
    if (timeSinceAttack < cooldown)
        return false;

    Collider *collider = owner->getComponent<Collider>();
    if (!collider)
        return false;

    Collider *playerCollider = other->getComponent<Collider>();
    if (!playerCollider)
        return false;

    Collider reachCollider = *collider;
    reachCollider.addSize({reach, reach});
    const Vector overlap = reachCollider.getOverlap(playerCollider->getBoundingBox());
    if (overlap.x == 0 || overlap.y == 0)
        return false;

    Health *playerHealth = other->getComponent<Health>();
    if (!playerHealth)
        return false;

    Vector knockbackDir = playerCollider->getPosition() - collider->getPosition();
    knockbackDir.normalize();
    knockbackDir.y = std::min(static_cast<float>(-scoop), knockbackDir.y);
    playerHealth->hurtKnockback(damage, knockback, knockbackDir);

    timeSinceAttack = 0.0f;
    return true;
}