#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include "Vector.hpp"
#include "ResourceManager.hpp"
#include "enums/Tile.hpp"

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

    bool init(const std::string &title, int width, int height, bool fullscreen);
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
    std::vector<Collider *> colliders;
    std::vector<Camera *> cameras;

protected:
    ResourceManager *resourceManager;

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<SDL_Texture *> backgrounds;
    float deltaTime;
    unsigned int lastFrameTime;
    int gravity;
    int maxFallSpeed;
    std::vector<GameObject *> gameObjects;
    GameObject *player;
    std::vector<std::vector<Tile>> tiles;
    int tileSize = 32;
    Vector tileMapOffset = {-30, -10};
    std::map<Tile, SDL_Texture *> tileTextures;

    void createTiles();
    void createGameObjects();
    void handleCollisions(GameObject *gameobject);
    void resolveCollisions(Transform *transform, Collider *collider, BoundingBox other);
    void renderTiles();
    void renderUi();
};