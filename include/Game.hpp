#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include "Vector.hpp"
#include "enums/Tile.hpp"
#include "ResourceManager.hpp"

using namespace std;

class BoundingBox;
class GameObject;
class Transform;
class Collider;

class Game
{
public:
    Game();
    ~Game();

    bool init(const string &title, int width, int height, bool fullscreen);
    void handleEvents();
    bool setTile(Vector tilePos, Tile tile);
    void update();
    void render();
    void cleanUp();

    bool isRunning() const { return running; }
    Vector getTilePos(Vector worldPos) const { return {floor(worldPos.x / tileSize), floor(worldPos.y / tileSize)}; }
    Tile getTile(Vector tilePos) const { return tiles[tilePos.y][tilePos.x]; }

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
    vector<GameObject *> gameObjects;
    vector<Collider *> colliders;
    vector<vector<Tile>> tiles;
    int tileSize = 32;
    map<Tile, SDL_Texture *> tileTextures;

    void createTiles();
    void createGameObjects();
    void resolveCollisions(Transform *transform, Collider *collider, BoundingBox other);
    void renderTiles();
};