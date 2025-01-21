#include "PlayerBehaviour.hpp"
#include "Component.hpp"
#include "GameObject.hpp"

class Transform;

void PlayerBehaviour::handleEvents(SDL_Event &event)
{
    const int movementSpeed = 300;
    const int jumpPower = 800;

    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
    {
        return;
    }

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        bool keyDown = (event.type == SDL_KEYDOWN);

        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            transform->setVelocityX(keyDown ? -movementSpeed : 0);
            break;
        case SDLK_d:
            transform->setVelocityX(keyDown ? movementSpeed : 0);
            break;
        case SDLK_SPACE:
            if (keyDown)
            {
                transform->setVelocityY(-jumpPower);
            }
        }
    }

    if (event.type == SDL_CONTROLLERAXISMOTION)
    {
        if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
        {
            float movementNormalized = ((event.caxis.value >= 1000 || event.caxis.value <= -1000) ? event.caxis.value * 0.00005 : 0);
            transform->setVelocityX(movementNormalized * movementSpeed);
        }
    }

    if (event.type == SDL_CONTROLLERBUTTONDOWN)
    {
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
        {
            transform->setVelocityY(-jumpPower);
        }
    }
}