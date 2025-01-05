#include "Game.hpp"
#include "GameObject.hpp"
#include <iostream>

Game::Game()
    : running(false), window(nullptr), renderer(nullptr), gravity(10)
{
}

Game::~Game()
{
    clean();
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

    // Create environment
    gravity = 10;
    gameObjects.push_back(GameObject(renderer, "Player1", 200, 50, (SDL_Color){255, 0, 0, 255}));
    gameObjects.push_back(GameObject(renderer, "Player2", width - 200, 50, (SDL_Color){0, 0, 255, 255}));

    running = true;
    return true;
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
            }
            break;
        default:
            break;
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

    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i].update(deltaTime, winWidth, winHeight, gravity);
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i].render();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
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

    SDL_Quit();
}