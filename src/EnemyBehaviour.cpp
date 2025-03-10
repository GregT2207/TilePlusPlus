#include "EnemyBehaviour.hpp"
#include "GameObject.hpp"
#include "MovementBehaviour.hpp"

void EnemyBehaviour::update(float deltaTime)
{
    if (!player)
        return;

    timeSinceAttack += deltaTime;
    if (timeSinceAttack < cooldown)
        return;

    followPlayer();
    if (attackPlayer())
        timeSinceAttack = 0;
}

void EnemyBehaviour::followPlayer()
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return;

    Transform *playerTransform = player->getComponent<Transform>();
    if (!playerTransform)
        return;

    Vector direction = (playerTransform->getPosition() - transform->getPosition());

    if (direction.x != 0)
        transform->addVelocityX(direction.normalized().x);

    if (direction.y < -(transform->getSize().y * 0.9f))
    {
        MovementBehaviour *mb = owner->getComponent<MovementBehaviour>();
        if (mb)
            mb->jump();
    }
}

bool EnemyBehaviour::attackPlayer()
{
    Collider *collider = owner->getComponent<Collider>();
    if (!collider)
        return false;

    Collider *playerCollider = player->getComponent<Collider>();
    if (!playerCollider)
        return false;

    BoundingBox bb = collider->getBoundingBox();
    if (!collider->contains(playerCollider->getPosition(), reach))
        return false;

    Health *playerHealth = player->getComponent<Health>();
    if (!playerHealth)
        return false;

    Vector knockbackDir = playerCollider->getPosition() - collider->getPosition();
    knockbackDir.normalize();
    knockbackDir.y = std::min(static_cast<float>(-scoop), knockbackDir.y);
    playerHealth->hurtKnockback(damage, knockback, knockbackDir);

    return true;
}