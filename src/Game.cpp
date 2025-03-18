#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test.h>
#include <SDL2/SDL_mixer.h>
#include "Game.hpp"
#include "GameObject.hpp"
#include "components/Camera.hpp"
#include "enums/Tile.hpp"

using namespace std;

Game::~Game()
{
    SDL_Quit();
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
    SDL_Window *sdlWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        flags);
    if (!sdlWindow)
    {
        cerr << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    window.reset(sdlWindow);

    // Create renderer
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer)
    {
        cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }
    renderer.reset(sdlRenderer);
    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);

    // Load resources
    resourceManager = make_unique<ResourceManager>(renderer.get());
    if (!resourceManager->init())
    {
        cerr << "Resources could not load!" << endl;
        return false;
    }

    backgrounds.push_back(resourceManager->loadTexture("backgrounds/sky.png"));
    backgrounds.push_back(resourceManager->loadTexture("backgrounds/mountains.png"));
    backgrounds.push_back(resourceManager->loadTexture("backgrounds/clouds.png"));

    // Load audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    Mix_Music *music = Mix_LoadMUS("../assets/audio/night.wav");
    if (!music)
    {
        cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << endl;
        return false;
    }
    // Mix_PlayMusic(music, -1);

    // Set up environment
    physicsManager = make_unique<PhysicsManager>(this, 2000, 1000, 1, 6);
    createTiles();
    createGameObjects();

    running = true;
    return true;
}

void Game::createTiles()
{
    tileTextures.insert({Tile::Dirt, resourceManager->loadTexture("sprites/dirt.jpg")});
    tileTextures.insert({Tile::Grass, resourceManager->loadTexture("sprites/grass.jpg")});
    tileTextures.insert({Tile::Water, resourceManager->loadTexture("sprites/water.png")});

    vector<Tile> airRow = {};
    vector<Tile> grassRow = {};
    vector<Tile> dirtRow = {};
    for (int i = 0; i < 200; i++)
    {
        airRow.push_back(Tile::Air);
        grassRow.push_back(rand() % 3 == 1 ? Tile::Water : Tile::Grass);
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

    for (int i = 0; i < 30; i++)
    {
        tiles.push_back(dirtRow);
    }
}

void Game::createGameObjects()
{
    player = new GameObject(this, "Greg");
    player->addComponent<Transform>(Vector{0.0f, 0.0f}, Vector{100.0f, 100.0f}, Vector{70.0f, 100.0f});
    player->addComponent<Collider>(Vector{70.0f, 100.0f});
    player->addComponent<Health>(100, 25);
    player->addComponent<Renderer>(renderer.get(), resourceManager.get(), "sprites/player.png");
    player->addComponent<Camera>(1440, 896);
    player->addComponent<PlayerBehaviour>();
    player->addComponent<MovementBehaviour>();
    player->addComponent<AttackBehaviour>(30, 700, 1, 2);
    player->addComponent<Inventory>(resourceManager.get());
    gameObjects.push_back(player);

    GameObject *enemy = new GameObject(this, "Flobbage Jr.");
    enemy->addComponent<Transform>(Vector{300.0f, -600.0f}, Vector{0.0f, 0.0f}, Vector{70.0f, 100.0f});
    enemy->addComponent<Collider>(Vector{70.0f, 100.0f});
    enemy->addComponent<Health>(20, 18);
    enemy->addComponent<Renderer>(renderer.get(), resourceManager.get(), "sprites/enemy.png");
    enemy->addComponent<EnemyBehaviour>(player);
    enemy->addComponent<MovementBehaviour>();
    enemy->addComponent<AttackBehaviour>(5, 500, 2, 0, 2);
    gameObjects.push_back(enemy);

    for (auto *gameObject : gameObjects)
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

        for (auto *gameObject : gameObjects)
        {
            gameObject->handleEvents(event);
        }
    }
}

Vector Game::worldPosToTileIndices(Vector worldPos) const
{
    return {floor((worldPos.x - tileMapOffset.x * tileSize) / tileSize), floor((worldPos.y - tileMapOffset.y * tileSize) / tileSize)};
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
    deltaTime = min(0.1f, (currentFrameTime - lastFrameTime) / 1000.0f);
    lastFrameTime = currentFrameTime;

    for (auto *gameObject : gameObjects)
    {
        gameObject->update(deltaTime);
        physicsManager->handleCollisions(gameObject);
    }
}

void Game::render()
{
    // Reset
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    // Background
    for (SDL_Texture *background : backgrounds)
    {
        SDL_RenderCopy(renderer.get(), background, nullptr, nullptr);
    }

    // Info
    SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
    SDLTest_DrawString(renderer.get(), 10, 10, "Greg's Game");
    Vector playerPos = player->getComponent<Transform>()->getPosition();
    SDLTest_DrawString(renderer.get(), 10, 40, (to_string(static_cast<int>(round(playerPos.x))) + " " + to_string(static_cast<int>(round(playerPos.y)))).c_str());
    SDLTest_DrawString(renderer.get(), 10, 70, (to_string(static_cast<int>(floor(1.0f / deltaTime))) + "FPS").c_str());

    // Game
    renderTiles();
    for (auto *gameObject : gameObjects)
    {
        gameObject->render(renderer.get());
    }
    renderUi();

    SDL_RenderPresent(renderer.get());
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
                for (Camera *camera : cameras)
                {
                    SDL_Rect tileRect = camera->worldRectToScreenRect({static_cast<int>((x + tileMapOffset.x) * tileSize), static_cast<int>((y + tileMapOffset.y) * tileSize), tileSize, tileSize});
                    SDL_RenderCopy(renderer.get(), tileTexture, nullptr, &tileRect);
                }
            }
        }
    }
}

void Game::renderUi()
{
    if (!player)
        return;

    Inventory *inv = player->getComponent<Inventory>();
    if (!inv)
        return;

    SDL_Rect nextRect = {10, 10, 100, 100};
    std::vector<Item *> items = inv->getItems();
    for (int i = 0; i < 5; i++)
    {
        // Render squares around slots
        if (i == inv->activeItem)
        {
            SDL_Rect outlineDestRect = {nextRect.x - 5, nextRect.y - 5, nextRect.w + 10, nextRect.h + 10};
            SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
            SDL_RenderFillRect(renderer.get(), &outlineDestRect);
        }
        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 180);
        SDL_RenderFillRect(renderer.get(), &nextRect);

        if (i < items.size() && items[i] != nullptr)
        {
            // Render texture and name
            SDL_Rect textureDestRect = {nextRect.x + 5, nextRect.y + 5, nextRect.w - 10, nextRect.h - 10};
            SDL_RenderCopy(renderer.get(), items[i]->getTexture(), nullptr, &textureDestRect);

            SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
            SDLTest_DrawString(renderer.get(), nextRect.x + 5, nextRect.y + 30, items[i]->name.c_str());
        }

        nextRect.x += 110;
    }
}