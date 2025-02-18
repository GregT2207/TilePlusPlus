#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test.h>
#include "Game.hpp"
#include "GameObject.hpp"
#include "PlayerBehaviour.hpp"
#include "enums/Tile.hpp"

Game::Game() : running(false), window(nullptr), renderer(nullptr), resourceManager(nullptr), gravity(10) {}
Game::~Game()
{
    cleanUp();
}

bool Game::init(const string &title, int width, int height, bool fullscreen)
{
    // Flags
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    SDL_GameController *controller = SDL_GameControllerOpen(0);
    if (controller)
    {
        cout << "Controller connected: " << SDL_GameControllerName(controller) << endl;
    }
    else
    {
        cerr << "No controller found" << endl;
    }

    // Create window
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        flags);
    if (!window)
    {
        cerr << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    // Load resources
    resourceManager = ResourceManager(renderer);
    if (!resourceManager.init())
    {
        cerr << "Resources could not load!" << endl;
        return false;
    }
    background = resourceManager.loadTexture("backgrounds/background.png");

    // Set up environment
    gravity = 2000;
    createTiles();
    createGameObjects();

    running = true;
    return true;
}

void Game::createTiles()
{
    tileTextures.insert({Tile::Dirt, resourceManager.loadTexture("sprites/dirt.jpg")});
    tileTextures.insert({Tile::Grass, resourceManager.loadTexture("sprites/grass.jpg")});

    vector<Tile> airRow = {};
    vector<Tile> grassRow = {};
    vector<Tile> dirtRow = {};
    for (int i = 0; i < 45; i++)
    {
        airRow.push_back(Tile::Air);
        grassRow.push_back(Tile::Grass);
        dirtRow.push_back(Tile::Dirt);
    }

    for (int i = 0; i < 12; i++)
    {
        tiles.push_back(airRow);
    }

    for (int i = 0; i < 1; i++)
    {
        tiles.push_back(grassRow);
    }

    for (int i = 0; i < 15; i++)
    {
        tiles.push_back(dirtRow);
    }
}

void Game::createGameObjects()
{
    gravity = 2000;

    GameObject *player = new GameObject(this, "Greg");
    player->addComponent<Transform>(Vector{40.0f, 0.0f}, Vector{0.0f, 0.0f}, Vector{70.0f, 100.0f});
    colliders.push_back(player->addComponent<Collider>(Vector{70.0f, 100.0f}));

    player->addComponent<SpriteRenderer>(resourceManager, "sprites/player.png");
    player->addComponent<PlayerBehaviour>();
    gameObjects.push_back(player);

    GameObject *enemy = new GameObject(this, "Flobbage Jr.");
    enemy->addComponent<Transform>(Vector{200.0f, 0.0f}, Vector{0.0f, 0.0f}, Vector{70.0f, 100.0f});
    colliders.push_back(enemy->addComponent<Collider>(Vector{70.0f, 100.0f}));
    enemy->addComponent<SpriteRenderer>(resourceManager, "sprites/enemy.png");
    gameObjects.push_back(enemy);

    for (auto &gameObject : gameObjects)
    {
        gameObject->init();
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            running = false;
            return;
        }

        for (auto &gameObject : gameObjects)
        {
            gameObject->handleEvents(event);
        }
    }
}

bool Game::setTile(Vector tilePos, Tile tile)
{
    try
    {
        tiles.at(tilePos.y).at(tilePos.x) = tile;
        return true;
    }
    catch (const std::out_of_range &e)
    {
        return false;
    }
}

void Game::update()
{
    unsigned int currentFrameTime = SDL_GetTicks64();
    deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
    lastFrameTime = currentFrameTime;

    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    for (auto &gameObject : gameObjects)
    {
        gameObject->update(deltaTime, winWidth, winHeight, gravity);

        Transform *transform = gameObject->getComponent<Transform>();
        Collider *collider = gameObject->getComponent<Collider>();
        if (transform && collider && !collider->isStatic)
        {
            // Resolve collisions for game objects
            for (auto &otherCollider : colliders)
            {
                if (collider == otherCollider)
                {
                    continue;
                }

                resolveCollisions(transform, collider, otherCollider->getBoundingBox());
            }

            // Resolve collisions for tiles
            BoundingBox boundingBox = collider->getBoundingBox();

            int yRangeStart = ((boundingBox.y - (static_cast<int>(boundingBox.y) % tileSize)) / tileSize) - 2;
            int yRangeEnd = ((boundingBox.y + boundingBox.h) - (static_cast<int>(boundingBox.y + boundingBox.h) % tileSize)) / tileSize + 1;
            int xRangeStart = ((boundingBox.x - (static_cast<int>(boundingBox.x) % tileSize)) / tileSize) - 2;
            int xRangeEnd = ((boundingBox.x + boundingBox.w) - (static_cast<int>(boundingBox.x + boundingBox.w) % tileSize)) / tileSize + 1;

            for (int y = yRangeStart; y < yRangeEnd; y++)
            {
                if (y >= tiles.size())
                    continue;

                for (int x = xRangeStart; x < xRangeEnd; x++)
                {
                    if (x >= tiles[y].size())
                        continue;

                    if (tiles[y][x] != Tile::Air)
                    {
                        resolveCollisions(transform, collider, {static_cast<float>(x * tileSize), static_cast<float>(y * tileSize), static_cast<float>(tileSize), static_cast<float>(tileSize)});
                    }
                }
            }
        }
    }
}

void Game::resolveCollisions(Transform *transform, Collider *collider, BoundingBox other)
{
    Vector overlap = collider->getOverlap(other);
    if (overlap.y != 0)
    {
        transform->addY(-overlap.y * 1.0f + 1.0f);
        transform->setVelocityY(0);
        collider->followTransform();
    }

    overlap = collider->getOverlap(other);
    if (overlap.x != 0)
    {
        transform->addX(-overlap.x * 1.0f + 1.0f);
        transform->setVelocityX(0);
        collider->followTransform();
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDLTest_DrawString(renderer, 10, 10, "Greg's Game");
    SDLTest_DrawString(renderer, 10, 40, (std::to_string(static_cast<int>(round(1.0f / deltaTime))) + "FPS").c_str());

    renderTiles();
    for (auto &gameObject : gameObjects)
    {
        gameObject->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::renderTiles()
{
    for (int y = 0; y < tiles.size(); y++)
    {
        for (int x = 0; x < tiles[y].size(); x++)
        {
            SDL_Texture *tileTexture = tileTextures[tiles[y][x]];

            if (tileTexture)
            {

                SDL_Rect tileRect = {x * tileSize, y * tileSize, tileSize, tileSize};
                SDL_RenderCopy(renderer, tileTexture, nullptr, &tileRect);
            }
        }
    }
}

void Game::cleanUp()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (background)
    {
        SDL_DestroyTexture(background);
    }

    SDL_Quit();
}