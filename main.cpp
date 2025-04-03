#include "class/Game/Game.cpp"


int main()
{
    Game *game = new Game();
    game->startGame();
    delete game;
    return 0;
}