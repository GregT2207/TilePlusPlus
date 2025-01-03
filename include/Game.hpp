#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <GameObject.hpp>

class Game
{
public:
    Game();
    ~Game();

    bool init(const std::string &title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning() const { return running; }

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<GameObject> gameObjects;
};