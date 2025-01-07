#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"
#include "Player.hpp"

Game::Game() : running(false), window(nullptr), renderer(nullptr), gravity(10) {}
Game::~Game()
{
    cleanUp();
}

bool Game::init(const std::string &title, int width, int height, bool fullscreen)
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
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GameController *controller = SDL_GameControllerOpen(0);
    if (controller)
    {
        std::cout << "Controller connected: " << SDL_GameControllerName(controller) << std::endl;
    }
    else
    {
        std::cerr << "No controller found" << std::endl;
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
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Load background texture
    SDL_Surface *backgroundSurface = IMG_Load("../assets//backgrounds/forest.jpeg");
    if (!backgroundSurface)
    {
        std::cerr << "Failed to load background image! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    background = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    gravity = 2000;
    createGameObjects();

    running = true;
    return true;
}

void Game::createGameObjects()
{
    gravity = 2000;

    GameObject *player = new Player("Greg");
    player->transform = new Transform(player, {400.0f, 10.0f}, {0.0f, 0.0f}, {50.0f, 100.0f});
    player->spriteRenderer = new SpriteRenderer(player, renderer, "sprites/player.png");

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

    for (auto &gameObject : gameObjects)
    {
        gameObject->render(renderer);
    }

    SDL_RenderPresent(renderer);
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