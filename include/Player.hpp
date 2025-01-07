#pragma once
#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player(std::string name);

    void handleEvents(SDL_Event &event) override;
};