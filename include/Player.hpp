#pragma once

#include <GameObject.hpp>

class Player : public GameObject
{
    Player(SDL_Renderer *renderer, std::string name, int x, int y);

    void handleEvents(SDL_Event event);
};