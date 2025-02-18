#include "Game.hpp"

int main(int argc, char *argv[])
{
    Game game;

    if (!game.init("Greg's Game", 1440, 896, false))
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
