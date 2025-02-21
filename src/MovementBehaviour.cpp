#include "MovementBehaviour.hpp"
#include "GameObject.hpp"

void MovementBehaviour::jump()
{
    Transform *transform = owner->getComponent<Transform>();
    Collider *collider = owner->getComponent<Collider>();

    if (transform && collider && collider->isGrounded())
    {
        transform->setVelocityY(-jumpPower);
    }
}