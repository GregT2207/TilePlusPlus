#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "enums/Tile.hpp"
#include "ResourceManager.hpp"

class GameObject;
class Collider;

class Game
{
public:
    Game();
    ~Game();

    bool init(const std::string &title, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void checkCollisions();
    void render();
    void cleanUp();

    bool isRunning() const
    {
        return running;
    }

    static constexpr float maxFallSpeed = 1000.0f;

protected:
    ResourceManager resourceManager;

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    float deltaTime;
    unsigned int lastFrameTime;
    int gravity;
    std::vector<GameObject *> gameObjects;
    std::vector<Collider *> colliders;
    std::vector<std::vector<Tile>> tiles;

    void createTiles();
    void createGameObjects();
    void renderTiles();
};