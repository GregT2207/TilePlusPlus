#pragma once
#include <SDL2/SDL.h>
#include "Vector.hpp"

class Game;
class GameObject;

class Camera
{
public:
    Camera(Game *game, int width, int height, GameObject *attachment = nullptr) : game(game), width(width), height(height), attachment(attachment) {};

    void attach(GameObject *newAttachment) { attachment = newAttachment; }
    Vector getPos() const;
    Vector getScreenPos(Vector vector) const;
    Vector getWorldPos(Vector vector) const;
    SDL_Rect getWorldPos(SDL_Rect rect) const;

    int width;
    int height;

private:
    Game *game;
    GameObject *attachment;
};