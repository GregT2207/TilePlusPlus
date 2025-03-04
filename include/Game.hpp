#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include "Vector.hpp"
#include "ResourceManager.hpp"
#include "enums/Tile.hpp"

using namespace std;

class BoundingBox;
class GameObject;
class Transform;
class Collider;
class Camera;

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
    Tile getTile(Vector tilePos) const { return tiles[tilePos.y][tilePos.x]; }
    Vector worldPosToTileIndices(Vector worldPos) const;
    int getGravity() const { return gravity; }
    int getMaxFallSpeed() const { return maxFallSpeed; }
    vector<Collider *> colliders;
    vector<Camera *> cameras;

protected:
    ResourceManager *resourceManager;

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    float deltaTime;
    unsigned int lastFrameTime;
    int gravity;
    int maxFallSpeed;
    vector<GameObject *> gameObjects;
    GameObject *player;
    vector<vector<Tile>> tiles;
    int tileSize = 32;
    Vector tileMapOffset = {-30, -10};
    map<Tile, SDL_Texture *> tileTextures;

    void createTiles();
    void createGameObjects();
    void handleCollisions(GameObject *gameobject);
    void resolveCollisions(Transform *transform, Collider *collider, BoundingBox other);
    void renderTiles();
    void renderUi();
};