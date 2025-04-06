#include "class/Game/Game.hpp"


int main()
{
    Game *game = new Game();
    game->startGame();
    delete game;
    return 0;
}

