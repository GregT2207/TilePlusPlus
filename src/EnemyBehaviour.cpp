#include "EnemyBehaviour.hpp"
#include "GameObject.hpp"
#include "MovementBehaviour.hpp"

void EnemyBehaviour::update(float deltaTime)
{
    followPlayer();
}

void EnemyBehaviour::followPlayer()
{
    if (!player)
        return;

    Transform *playerTransform = player->getComponent<Transform>();
    if (!playerTransform)
        return;

    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return;

    Vector direction = (playerTransform->getPosition() - transform->getPosition()).normalized();

    if (direction.x != 0)
        transform->addVelocityX(direction.x);

    if (direction.y < 0)
    {
        MovementBehaviour *mb = owner->getComponent<MovementBehaviour>();
        if (mb)
            mb->jump();
    }
}