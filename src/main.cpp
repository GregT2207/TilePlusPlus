#include "Game.hpp"

int main(int argc, char *argv[])
{
    Game game;

    if (!game.init("Test Game", 1280, 720, false))
    {
        return 1;
    }

    while (game.isRunning())
    {
        game.handleEvents();
        game.update();
        game.render();
    }

    return 0;
}