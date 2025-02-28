#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test.h>
#include <SDL2/SDL_mixer.h>
#include "Game.hpp"
#include "GameObject.hpp"
#include "Collider.hpp"
#include "Camera.hpp"
#include "enums/Tile.hpp"

Game::Game() : running(false), window(nullptr), renderer(nullptr), resourceManager(nullptr), gravity(2000), maxFallSpeed(1000) {}
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
    createTiles();
    createGameObjects();

    running = true;
    return true;
}

void Game::createTiles()
{
    tileTextures.insert({Tile::Dirt, resourceManager.loadTexture("sprites/dirt.jpg")});
    tileTextures.insert({Tile::Grass, resourceManager.loadTexture("sprites/grass.jpg")});
    tileTextures.insert({Tile::Water, resourceManager.loadTexture("sprites/water.png")});

    vector<Tile> airRow = {};
    vector<Tile> grassRow = {};
    vector<Tile> dirtRow = {};
    for (int i = 0; i < 45; i++)
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

    for (int i = 0; i < 15; i++)
    {
        tiles.push_back(dirtRow);
    }
}

void Game::createGameObjects()
{
    GameObject *player = new GameObject(this, "Greg");
    player->addComponent<Transform>(Vector{0.0f, 0.0f}, Vector{10.0f, 10.0f}, Vector{70.0f, 100.0f});
    player->addComponent<Collider>(Vector{70.0f, 100.0f});
    player->addComponent<SpriteRenderer>(resourceManager, "sprites/player.png");
    player->addComponent<Camera>(1440, 896);
    player->addComponent<PlayerBehaviour>();
    player->addComponent<MovementBehaviour>();
    gameObjects.push_back(player);

    GameObject *enemy = new GameObject(this, "Flobbage Jr.");
    enemy->addComponent<Transform>(Vector{1000.0f, 60.0f}, Vector{0.0f, 0.0f}, Vector{70.0f, 100.0f});
    enemy->addComponent<Collider>(Vector{70.0f, 100.0f});
    enemy->addComponent<SpriteRenderer>(resourceManager, "sprites/enemy.png");
    // enemy->addComponent<EnemyBehaviour>(player);
    // enemy->addComponent<MovementBehaviour>();
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

    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    for (auto &gameObject : gameObjects)
    {
        gameObject->update(deltaTime);
        handleCollisions(gameObject);
    }
}

void Game::handleCollisions(GameObject *gameObject)
{
    Transform *transform = gameObject->getComponent<Transform>();
    Collider *collider = gameObject->getComponent<Collider>();

    if (transform && collider && !collider->isStatic)
    {
        collider->setGrounded(false);

        // Handle collisions for game objects
        for (Collider *otherCollider : colliders)
        {
            if (collider == otherCollider)
            {
                continue;
            }

            resolveCollisions(transform, collider, otherCollider->getBoundingBox());
        }

        // Handle collisions for tiles
        BoundingBox boundingBox = collider->getBoundingBox();

        int yRangeStart = ((boundingBox.y - (static_cast<int>(boundingBox.y) % tileSize)) / tileSize) - 2 - tileMapOffset.y;
        int yRangeEnd = ((boundingBox.y + boundingBox.h) - (static_cast<int>(boundingBox.y + boundingBox.h) % tileSize)) / tileSize + 1 - tileMapOffset.y;
        int xRangeStart = ((boundingBox.x - (static_cast<int>(boundingBox.x) % tileSize)) / tileSize) - 2 - tileMapOffset.x;
        int xRangeEnd = ((boundingBox.x + boundingBox.w) - (static_cast<int>(boundingBox.x + boundingBox.w) % tileSize)) / tileSize + 1 - tileMapOffset.x;

        float waterOverlap = 0.0f;

        for (int y = yRangeStart; y < yRangeEnd; y++)
        {
            if (y < 0 || y >= tiles.size())
                continue;

            for (int x = xRangeStart; x < xRangeEnd; x++)
            {
                if (x < 0 || x >= tiles[y].size())
                    continue;

                if (tiles[y][x] == Tile::Air)
                {
                    continue;
                }

                BoundingBox tileBb = {static_cast<int>((x + tileMapOffset.x) * tileSize), static_cast<int>((y + tileMapOffset.y) * tileSize), tileSize, tileSize};

                if (tiles[y][x] == Tile::Water)
                {
                    Vector overlap = collider->getOverlap(tileBb);
                    waterOverlap = max(waterOverlap, overlap.y);
                    continue;
                }

                resolveCollisions(transform, collider, tileBb);
            }
        }

        if (waterOverlap > 0)
        {
            const float defaultBuoyancy = 1.5f;
            const float bobbingBuoyancy = defaultBuoyancy * 3.0f;

            float waterBuoyancy = 0.0f;
            if ((waterOverlap > tileSize * 0.1f) && (waterOverlap < tileSize * 0.2f))
            {
                waterBuoyancy = transform->getVelocity().y > 0 ? defaultBuoyancy : bobbingBuoyancy;
            }
            else if (waterOverlap >= tileSize * 0.2f)
            {
                waterBuoyancy = defaultBuoyancy;
            }

            transform->addVelocityY(-waterBuoyancy * gravity * 0.01f);
        }
    }
}

void Game::resolveCollisions(Transform *transform, Collider *collider, BoundingBox other)
{
    auto resolveAxis = [transform, collider](char axis, float overlap = 0.0f) -> void
    {
        if (axis == 'x')
        {
            transform->addX(-overlap);
            if ((overlap < 0 && transform->getVelocity().x < 0) || (overlap > 0 && transform->getVelocity().x > 0))
                transform->setVelocityX(0);
        }
        else
        {
            transform->addY(-overlap);
            if ((overlap < 0 && transform->getVelocity().y < 0) || (overlap > 0 && transform->getVelocity().y > 0))
                transform->setVelocityY(0);
        }

        collider->followTransform();
    };

    Vector overlap = collider->getOverlap(other);
    if (overlap.x == 0 && overlap.y == 0)
        return;

    if (overlap.y > 0)
        collider->setGrounded(true);

    fabs(overlap.x) < fabs(overlap.y) ? resolveAxis('x', overlap.x) : resolveAxis('y', overlap.y);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDLTest_DrawString(renderer, 10, 10, "Greg's Game");
    Vector playerPos = gameObjects[0]->getComponent<Transform>()->getPosition();
    SDLTest_DrawString(renderer, 10, 40, (to_string(static_cast<int>(round(playerPos.x))) + " " + to_string(static_cast<int>(round(playerPos.y)))).c_str());
    SDLTest_DrawString(renderer, 10, 70, (to_string(static_cast<int>(floor(1.0f / deltaTime))) + "FPS").c_str());

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
                for (Camera *camera : cameras)
                {
                    SDL_Rect tileRect = camera->worldRectToScreenRect({static_cast<int>((x + tileMapOffset.x) * tileSize), static_cast<int>((y + tileMapOffset.y) * tileSize), tileSize, tileSize});
                    SDL_RenderCopy(renderer, tileTexture, nullptr, &tileRect);
                }
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