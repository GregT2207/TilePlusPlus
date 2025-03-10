#include "EnemyBehaviour.hpp"
#include "GameObject.hpp"
#include "MovementBehaviour.hpp"

void EnemyBehaviour::update(float deltaTime)
{
    if (!player)
        return;

    followPlayer();

    AttackBehaviour *ab = owner->getComponent<AttackBehaviour>();
    if (ab)
        ab->attack(player);
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