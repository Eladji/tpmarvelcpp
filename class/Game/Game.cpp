#include "Game.hpp"
#include <chrono>
#include <thread>
Game::Game()
{
    this->turn = 0;

    cout << "Enter the number of players: ";
    cin >> this->nb_players;
    this->game_over = false;
    cout << "Game created!" << endl;
    cout << "Welcome to the game!" << endl;
    cout << "The game will start in :" << endl;
    for (int i = 3; i > 0; i--)
    {
        cout << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

Game::~Game()
{
    for (auto player : player_list)
    {
        for (auto hero : player->getTeam())
        {
            player->removeHero(hero);
            delete &hero;
        }
        delete player;
    }
    player_list.clear();
    cout << "Game destroyed!" << endl;
}

void Game::startGame()
{
    cout << "Game started!" << endl;
    createPlayer();
    setTurn(1);
    cout << "Turn: " << turn << endl;
    while (!game_over)
    {
        nextTurn();
    }
}
void Game::createPlayer()
{
    for (int i = 0; i < this->nb_players; i++)
    {
        cout << "Player " << i + 1 << " Enter your name: ";
        string name;
        cin >> name;
        Player *player = new Player(name);
        this->addPlayer(player);
        cout << "Player " << player->getName() << " created!" << endl;
        createteam(player);
        player_list.push_back(player);
        cout << "Player " << player->getName() << " created!" << endl;
    }
}

void Game::createteam(Player *player)
{
    cout << "Choose your team:" << endl;
    cout << "1. Hulk" << endl;
    cout << "2. Spider Man" << endl;
    cout << "3. Iron Man" << endl;
    cout << "4. Doctor Strange" << endl;
    int choice;
    for (int i = 0; i < 4; i++)
    {

        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Hulk *hulk = new Hulk();
            player->addHero(*hulk);
            delete hulk;
            break;
        }
        case 2:
        {
            SpiderMan *spiderMan = new SpiderMan();
            player->addHero(*spiderMan);
            delete spiderMan;
            break;
        }
        case 3:
        {
            IronMan *ironMan = new IronMan();
            player->addHero(*ironMan);
            delete ironMan;
            break;
        }
        case 4:
        {
            DocteurStrange *docteurStrange = new DocteurStrange();
            player->addHero(*docteurStrange);
            delete docteurStrange;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
    cout << "Team created!" << endl;
    player->displayTeam();
    cout << "Choose your artefacts:" << endl;
    cout << "1. Cursed Stone" << endl;
    cout << "2. Health Potion" << endl;
    cout << "3. Power Amulet" << endl;
    for (int i = 0; i < 3; i++)
    {
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            CursedStone *cursedStone = new CursedStone();
            player->addArtefact(*cursedStone);
            delete cursedStone;
            break;
        }
        case 2:
        {
            HealthPotion *healthPotion = new HealthPotion();
            player->addArtefact(*healthPotion);
            delete healthPotion;
            break;
        }
        case 3:
        {
            PowerAmulet *powerAmulet = new PowerAmulet();
            player->addArtefact(*powerAmulet);
            delete powerAmulet;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
    cout << "Artefacts added!" << endl;
    player->displayInventory();
}

void Game::endGame()
{
    cout << "Game ended!" << endl;
}

void Game::nextTurn()
{
    for (auto player : player_list)
    {
        if (checkGameOver(player))
        {
            cout << player->getName() << " is out of the game!" << endl;
            displayWinner(player);
            endGame();
            return;
        }
        for (auto player : player_list)
        {
            action(player);
        }
        displayTurn();
    }

    setTurn(getTurn() + 1);
    cout << "Turn " << turn << endl;
}
void Game::displayTurn()
{
    cout << "Turn: " << turn << endl;
}
void Game::displayWinner(Player *player)
{
    cout << "Player " << player->getName() << " wins!" << endl;
}
void Game::setTurn(int turn)
{
    this->turn = turn;
}
int Game::getTurn()
{
    return this->turn;
}

void Game::action(Player *player)
{
    cout << "Choose your action:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Use Artefact" << endl;
    cout << "3. Switch Hero" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {

        player->getCurrentHero()->attack(selectTarget(player));
        break;
    }

    case 2:
    {
        cout << "Choose your artefact:" << endl;
        Artefacts *artselec = selectArtefact(player);
        artselec->use(selectTarget());
        break;
    }
    case 3:
    {
        player->setCurrentHero(player->getHero(0));
        cout << "You have switched to " << player->getCurrentHero()->getName() << endl;
        action(player);
        break;
    }
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
}

SuperHero &Game::selectTarget(Player *player = nullptr)
{
    cout << "Choose your target:" << endl;
    Player *targetPlayer = getPlayer();
    for (auto &p : player_list)
    {
        if (p != player)
        {
            targetPlayer = p;
            break;
        }
    }
    return *selectHero(targetPlayer);
}

bool Game::checkGameOver(Player *player)
{
    if (player->isTeamAlive() == false)
    {
        cout << "Player " << player->getName() << " is out of the game!" << endl;
        for (auto &hero : player->getTeam())
        {
            player->removeHero(hero);
            delete &hero;
        }
        player->getTeam().clear();
        this->removePlayer(player);
        return true;
    }
    return false;
}

Artefacts *Game::selectArtefact(Player *player)
{
    player->displayInventory();
    cout << "Select an artefact:" << endl;
    int choice;
    cin >> choice;
    return player->getArtefact(choice);
}
SuperHero *Game::selectHero(Player *player)
{
    cout << "Select a hero:" << endl;
    player->displayTeam();
    int choice;
    cin >> choice;
    return player->getHero(choice);
}

void Game::addPlayer(Player *player)
{
    player_list.push_back(player);
}
void Game::removePlayer(Player *player)
{
    auto it = find(player_list.begin(), player_list.end(), player);
    if (it != player_list.end())
    {
        player_list.erase(it);
        delete player;
        cout << "Player " << player->getName() << " removed!" << endl;
    }
}
void Game::displayPlayerList()
{
    cout << "Player list:" << endl;
    for (auto player : player_list)
    {
        cout << player->getName() << endl;
    }
}

Player *Game::getPlayer(int index = NULL)
{
    if (index == NULL)
    {
        displayPlayerList();
        cout << "Choose a player:" << endl;
        cin >> index;
    }
    if (index >= 0 && index < player_list.size())
    {
        return player_list[index];
    }
    return nullptr;
}
void Game::setNbPlayers(int nb_players)
{
    this->nb_players = nb_players;
}
int Game::getNbPlayers()
{
    return this->nb_players;
}
void Game::getPlayerList()
{
    cout << "Player list:" << endl;
    for (auto player : player_list)
    {
        cout << player->getName() << endl;
    }
}
