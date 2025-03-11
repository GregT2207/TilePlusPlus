#include "GameObject.hpp"
#include "components/MovementBehaviour.hpp"

void MovementBehaviour::jump()
{
    Transform *transform = owner->getComponent<Transform>();
    Collider *collider = owner->getComponent<Collider>();

    if (canJump && transform && collider && collider->isGrounded())
    {
        transform->setVelocityY(-jumpPower);
    }
}