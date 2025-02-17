#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test.h>
#include "Game.hpp"
#include "GameObject.hpp"
#include "PlayerBehaviour.hpp"
#include "enums/Tile.hpp"

class Transform;
class Collider;
class SpriteRenderer;

using namespace std;

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
    vector<Tile> airRow = {};
    vector<Tile> dirtRow = {};
    vector<Tile> stoneRow = {};
    for (int i = 0; i < 40; i++)
    {
        airRow.push_back(Tile::Air);
        dirtRow.push_back(Tile::Dirt);
        stoneRow.push_back(Tile::Stone);
    }

    for (int i = 0; i < 16; i++)
    {
        tiles.push_back(airRow);
    }

    for (int i = 0; i < 4; i++)
    {
        tiles.push_back(dirtRow);
    }

    for (int i = 0; i < 3; i++)
    {
        tiles.push_back(stoneRow);
    }
}

void Game::createGameObjects()
{
    gravity = 2000;

    GameObject *player = new GameObject("Greg");
    player->addComponent<Transform>(Vector{40.0f, 10.0f}, Vector{0.0f, 0.0f}, Vector{70.0f, 100.0f});
    colliders.push_back(player->addComponent<Collider>(Vector{70.0f, 100.0f}));

    player->addComponent<SpriteRenderer>(resourceManager, "sprites/player.png");
    player->addComponent<PlayerBehaviour>();
    gameObjects.push_back(player);

    GameObject *enemy = new GameObject("Flobbage Jr.");
    enemy->addComponent<Transform>(Vector{200.0f, 10.0f}, Vector{0.0f, 0.0f}, Vector{70.0f, 100.0f});
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
            for (auto &otherCollider : colliders)
            {
                if (collider == otherCollider)
                {
                    continue;
                }

                if (collider->intersects(*otherCollider))
                {
                    Transform *otherTransform = otherCollider->owner->getComponent<Transform>();

                    Transform *fasterTransform = transform->getVelocity().magnitude() > otherTransform->getVelocity().magnitude() ? transform : otherTransform;
                    Transform *slowerTransform = fasterTransform == transform ? otherTransform : transform;

                    Vector direction = fasterTransform->getPosition() - slowerTransform->getPosition();
                    direction.normalize();
                    fasterTransform->addPosition(direction * 0.02f);
                }
            }
        }
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
    const int tileSize = 32;

    for (int y = 0; y < tiles.size(); y++)
    {
        for (int x = 0; x < tiles[y].size(); x++)
        {
            switch (tiles[y][x])
            {
            case Tile::Air:
                continue;
                break;
            case Tile::Dirt:
                SDL_SetRenderDrawColor(renderer, 84, 45, 28, 255);
                break;
            case Tile::Stone:
                SDL_SetRenderDrawColor(renderer, 119, 115, 114, 255);
                break;
            }

            SDL_Rect tileRect = {x * tileSize, y * tileSize, tileSize, tileSize};
            SDL_RenderFillRect(renderer, &tileRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &tileRect);
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