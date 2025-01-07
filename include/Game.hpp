#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class GameObject;

class Game
{
public:
    Game();
    ~Game();

    bool init(const std::string &title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void cleanUp();
    void createEnvironment();

    bool isRunning() const
    {
        return running;
    }

    static constexpr float maxFallSpeed = 500.0f;

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    float deltaTime;
    unsigned int lastFrameTime;
    int gravity;
    std::vector<GameObject *> gameObjects;
};