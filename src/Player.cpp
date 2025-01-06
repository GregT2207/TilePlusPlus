#include <Player.hpp>

Player::Player(SDL_Renderer *renderer, std::string name, int x, int y)
    : GameObject(renderer, name, x, y)
{
    //
}

void Player::handleEvents(SDL_Event event)
{
    GameObject::handleEvents(event);

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
    {
        bool keyDown = (event.type == SDL_KEYDOWN);

        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            velocity.y = keyDown ? -200 : 0;
            break;
        }
    }
}
