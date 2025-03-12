#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include "geometry/Vector.hpp"
#include "enums/Tile.hpp"

class ResourceManager;
class PhysicsManager;
class BoundingBox;
class GameObject;
class Transform;
class Collider;
class Camera;

class Game
{
public:
    Game() : running(false), window(nullptr), renderer(nullptr), resourceManager(nullptr) {}
    ~Game();

    bool init(const std::string &title, int width, int height, bool fullscreen);
    void handleEvents();
    bool setTile(Vector tilePos, Tile tile);
    void update();
    void render();
    void cleanUp();

    bool isRunning() const { return running; }
    int getTileSize() const { return tileSize; }
    Vector getTileMapOffset() const { return tileMapOffset; }
    Tile getTile(Vector tilePos) const { return tiles[tilePos.y][tilePos.x]; }
    Vector worldPosToTileIndices(Vector worldPos) const;
    PhysicsManager *getPhysicsManager() const { return physicsManager; }
    std::vector<std::vector<Tile>> tiles;
    std::vector<Collider *> colliders;
    std::vector<Camera *> cameras;

protected:
    ResourceManager *resourceManager;
    PhysicsManager *physicsManager;

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<SDL_Texture *> backgrounds;
    float deltaTime;
    unsigned int lastFrameTime;
    std::vector<GameObject *> gameObjects;
    GameObject *player;
    int tileSize = 32;
    Vector tileMapOffset = {-30, -10};
    std::map<Tile, SDL_Texture *> tileTextures;

    void createTiles();
    void createGameObjects();
    void renderTiles();
    void renderUi();
};