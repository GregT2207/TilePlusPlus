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

    Vector direction = (playerTransform->getPosition() - transform->getPosition());

    if (direction.x != 0)
        transform->addVelocityX(direction.normalized().x);

    if (direction.y < -(transform->getSize().y * 0.9f))
    {
        MovementBehaviour *mb = owner->getComponent<MovementBehaviour>();
        // if (mb)
        //     mb->jump();
    }
}