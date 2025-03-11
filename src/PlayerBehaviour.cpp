#include "GameObject.hpp"
#include "components/PlayerBehaviour.hpp"
#include "components/Component.hpp"
#include "components/MovementBehaviour.hpp"
#include "components/Camera.hpp"

class Transform;
class Collider;

void PlayerBehaviour::handleEvents(SDL_Event &event)
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return;

    Inventory *inv = owner->getComponent<Inventory>();

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            movementVelocity = -keyboardMovementSpeed;
            transform->setDirection({-1.0f, 1.0f});
            break;
        case SDLK_d:
            movementVelocity = keyboardMovementSpeed;
            transform->setDirection({1.0f, 1.0f});
            break;
        case SDLK_SPACE:
            jumping = true;
            break;
        case SDLK_1:
            if (inv)
                inv->activeItem = 0;
            break;
        case SDLK_2:
            if (inv)
                inv->activeItem = 1;
            break;
        case SDLK_3:
            if (inv)
                inv->activeItem = 2;
            break;
        case SDLK_4:
            if (inv)
                inv->activeItem = 3;
            break;
        case SDLK_5:
            if (inv)
                inv->activeItem = 4;
            break;
        case SDLK_6:
            if (inv)
                inv->activeItem = 5;
            break;
        case SDLK_7:
            if (inv)
                inv->activeItem = 6;
            break;
        case SDLK_8:
            if (inv)
                inv->activeItem = 7;
            break;
        case SDLK_9:
            if (inv)
                inv->activeItem = 8;
            break;
        case SDLK_0:
            if (inv)
                inv->activeItem = 9;
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
            jumping = true;
            break;
        }

        break;

    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
            useItem();
        break;
    case SDL_MOUSEMOTION:
        if (event.button.button == SDL_BUTTON_LEFT)
            useItem();
        break;
    }
}

void PlayerBehaviour::update(float deltaTime)
{
    Transform *transform = owner->getComponent<Transform>();
    if (!transform)
        return;

    if (movementVelocity != 0)
        transform->setVelocityX(movementVelocity);

    if (jumping)
    {
        MovementBehaviour *mb = owner->getComponent<MovementBehaviour>();
        if (mb)
        {
            mb->jump();
            jumping = false;
        }
    }
}

Vector PlayerBehaviour::getClickedWorldPos()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    Camera *camera = owner->getComponent<Camera>();
    if (!camera)
        return {0, 0};

    return camera->screenPosToWorldPos({x, y});
}

void PlayerBehaviour::useItem()
{
    Inventory *inventory = owner->getComponent<Inventory>();
    if (!inventory)
        return;

    Item *item = inventory->getActiveItem();
    if (!item)
        return;

    if (item->getTile())
    {
        placeTile(getClickedWorldPos(), item->getTile().value());
        return;
    }

    if (item->name == "Midnight Slasher")
    {
        AttackBehaviour *ab = owner->getComponent<AttackBehaviour>();
        // if (ab)
        //     ab->attack();

        return;
    }

    if (item->name == "Cradle Picker")
    {
        placeTile(getClickedWorldPos(), Tile::Air);
        return;
    }
}

void PlayerBehaviour::placeTile(Vector worldPos, Tile tile)
{
    Vector tilePos = owner->game->worldPosToTileIndices(worldPos);

    if (tile == Tile::Air || owner->game->getTile(tilePos) == Tile::Air)
        owner->game->setTile(tilePos, tile);
}