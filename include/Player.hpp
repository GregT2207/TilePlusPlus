#pragma once
#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player();

    void handleEvents(SDL_Event &event) override;
};