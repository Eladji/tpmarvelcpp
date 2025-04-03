#include "Player/Player.cpp"
class Game
{
private:
    int turn;
    vector<Player*> player_list;
    int nb_players;
    bool game_over;

public:
    Game();
    ~Game();
    void startGame();
    void endGame();
    void nextTurn();
    void displayTurn();
    void displayWinner(Player* player);
    void createPlayer();
    Player* getPlayer(int index= NULL );
    void setTurn(int turn);
    int getTurn();
    void createteam(Player* player);
    void action(Player* player);
    bool checkGameOver(Player* player);
    Artefacts* selectArtefact(Player* player);
    SuperHero* selectHero(Player* player);
    void getPlayerList();
    void setNbPlayers(int nb_players);
    int getNbPlayers();
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    void displayPlayerList();
    SuperHero* selectTarget(Player *player = nullptr);
};
