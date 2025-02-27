#include "PlayerBehaviour.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include "MovementBehaviour.hpp"
#include "Camera.hpp"

class Transform;
class Collider;

void PlayerBehaviour::handleEvents(SDL_Event &event)
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return;

    MovementBehaviour *mb = owner->getComponent<MovementBehaviour>();

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            movementVelocity = -keyboardMovementSpeed;
            transform->setDirection({1.0f, 1.0f});
            break;
        case SDLK_d:
            movementVelocity = keyboardMovementSpeed;
            transform->setDirection({-1.0f, 1.0f});
            break;
        case SDLK_SPACE:
            if (mb)
                mb->jump();
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            if (transform->getVelocity().x < 0)
                movementVelocity = 0.0f;
            break;
        case SDLK_d:
            if (transform->getVelocity().x > 0)
                movementVelocity = 0.0f;
            break;
        }
        break;

    case SDL_CONTROLLERAXISMOTION:
        if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
        {
            float movementNormalized = ((event.caxis.value >= 1000 || event.caxis.value <= -1000) ? event.caxis.value * 0.00005 : 0);
            movementVelocity = movementNormalized * keyboardMovementSpeed;
        }
        break;

    case SDL_CONTROLLERBUTTONDOWN:
        switch (event.cbutton.button)
        {
        case SDL_CONTROLLER_BUTTON_A:
            if (mb)
                mb->jump();
            break;
        }

        break;

    case SDL_MOUSEBUTTONDOWN:
        checkTileActions(event);
        break;
    case SDL_MOUSEMOTION:
        checkTileActions(event);
        break;
    }
}

void PlayerBehaviour::update(float deltaTime)
{
    Transform *transform = owner->getComponent<Transform>();

    if (transform)
    {
        transform->setVelocityX(movementVelocity);
    }
}

void PlayerBehaviour::checkTileActions(SDL_Event &event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    Camera *camera = owner->getComponent<Camera>();
    if (!camera)
        return;

    Vector tilePos = camera->screenPosToWorldPos({x, y});

    switch (event.button.button)
    {
    case SDL_BUTTON_LEFT:
        destroyTile(tilePos);
        break;

    case SDL_BUTTON_RIGHT:
        placeTile(tilePos);
        break;
    }
}

void PlayerBehaviour::destroyTile(Vector mousePos)
{
    owner->game->setTile(owner->game->getTilePos(mousePos), Tile::Air);
}

void PlayerBehaviour::placeTile(Vector mousePos)
{
    Vector tilePos = owner->game->getTilePos(mousePos);

    if (owner->game->getTile(tilePos) == Tile::Air)
        owner->game->setTile(tilePos, Tile::Dirt);
}