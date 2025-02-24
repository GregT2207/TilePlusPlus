#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include "Renderer.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"
#include "enums/Tile.hpp"

using namespace std;

class BoundingBox;
class Renderer;
class ResourceManager;
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
    Camera *getCamera() const { return camera; }
    Vector getTilePos(Vector worldPos) const { return {floor(worldPos.x / tileSize), floor(worldPos.y / tileSize)}; }
    Tile getTile(Vector tilePos) const { return tiles[tilePos.y][tilePos.x]; }
    int getGravity() const { return gravity; }
    int getMaxFallSpeed() const { return maxFallSpeed; }

    Renderer *renderer;
    vector<Collider *> colliders;

protected:
    ResourceManager *resourceManager;

private:
    bool running;
    SDL_Window *window;
    SDL_Texture *background;
    float deltaTime;
    unsigned int lastFrameTime;
    int gravity;
    int maxFallSpeed;
    Camera *camera;
    vector<GameObject *> gameObjects;
    vector<vector<Tile>> tiles;
    int tileSize = 32;
    map<Tile, SDL_Texture *> tileTextures;

    void createTiles();
    void createGameObjects();
    void handleCollisions(GameObject *gameobject);
    void resolveCollisions(Transform *transform, Collider *collider, BoundingBox other);
    void renderTiles();
};