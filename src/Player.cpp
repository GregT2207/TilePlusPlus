#include "Player.hpp"

Player::Player(std::string name) : GameObject(name) {}

void Player::handleEvents(SDL_Event &event)
{
    GameObject::handleEvents(event);

    const int movementSpeed = 200;
    const int jumpPower = 300;

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        bool keyDown = (event.type == SDL_KEYDOWN);

        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            // velocity.x = keyDown ? -movementSpeed : -0;
            break;
        case SDLK_d:
            // velocity.x = keyDown ? movementSpeed : 0;
            break;
        case SDLK_SPACE:
            if (keyDown)
            {
                // velocity.y = -jumpPower;
            }
        }
    }
}