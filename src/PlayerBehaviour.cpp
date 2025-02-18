#include "PlayerBehaviour.hpp"
#include "Component.hpp"
#include "GameObject.hpp"

class Transform;
class Collider;

void PlayerBehaviour::handleEvents(SDL_Event &event)
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return;

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            transform->setVelocityX(-movementSpeed);
            break;
        case SDLK_d:
            transform->setVelocityX(movementSpeed);
            break;
        case SDLK_SPACE:
            jump();
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            if (transform->getVelocity().x < 0)
                transform->setVelocityX(0);
            break;
        case SDLK_d:
            if (transform->getVelocity().x > 0)
                transform->setVelocityX(0);
            break;
        }
        break;

    case SDL_CONTROLLERAXISMOTION:
        if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
        {
            float movementNormalized = ((event.caxis.value >= 1000 || event.caxis.value <= -1000) ? event.caxis.value * 0.00005 : 0);
            transform->setVelocityX(movementNormalized * movementSpeed);
        }
        break;

    case SDL_CONTROLLERBUTTONDOWN:
        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
            jump();
        break;

    case SDL_MOUSEBUTTONUP:
        int x, y;
        SDL_GetMouseState(&x, &y);

        switch (event.button.button)
        {
        case SDL_BUTTON_LEFT:
            destroyTile({x, y});
            break;

        case SDL_BUTTON_RIGHT:
            placeTile({x, y});
            break;
        }
        break;
    }
}

void PlayerBehaviour::jump()
{
    Transform *transform = owner->getComponent<Transform>();
    Collider *collider = owner->getComponent<Collider>();

    if (transform && collider && collider->isGrounded())
    {
        transform->setVelocityY(-jumpPower);
    }
}

void PlayerBehaviour::destroyTile(Vector mousePos)
{
    owner->game->setTile(owner->game->getTilePos(mousePos), Tile::Air);
}

void PlayerBehaviour::placeTile(Vector mousePos)
{
    owner->game->setTile(owner->game->getTilePos(mousePos), Tile::Dirt);
}