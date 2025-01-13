#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"
#include "Player.hpp"
#include "enums/Tile.hpp"

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
    background = resourceManager.loadTexture("backgrounds/forest.jpeg");

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

    GameObject *player = new Player("Greg");
    player->transform = new Transform(player, {400.0f, 10.0f}, {0.0f, 0.0f}, {50.0f, 100.0f});
    player->spriteRenderer = new SpriteRenderer(player, resourceManager, "sprites/player.png");

    gameObjects.push_back(player);

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
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, nullptr);

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