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
        
        for (int i = 0; i < static_cast<int>((player->getTeam().size())); i++)
        {
            player->removeHero(player->getHero(i));
            
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
        cout << choice << endl;
        switch (choice)
        {
        case 1:
        {
            
            player->addHero(new Hulk());
            break;
        }
        case 2:
        {
            player->addHero(new SpiderMan());
            break;
        }
        case 3:
        {
            player->addHero(new IronMan());
            break;
        }
        case 4:
        {
            player->addHero(new DocteurStrange());
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            i--;
            continue;
        }
        cout << "Hero " << player->getHero(i)->getName() << " created!" << endl;
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
            player->addArtefact(new CursedStone());
            break;
        }
        case 2:
        {
            player->addArtefact(new HealthPotion());
            break;
        }
        case 3:
        {
            player->addArtefact(new PowerAmulet());
            break;
        }
        default:
        {
        cout << "Invalid choice!" << endl;
        i--;
        continue;
        }
    }
    cout << "Artefact " << player->getArtefact(i)->getName() << " created!" << endl;
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
    int choice = 0;
    bool validInput = false;
    
    while (!validInput) {
        cout << "Choose your action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use Artefact" << endl;
        cout << "3. Switch Hero" << endl;
        
        // Clear input buffer and ensure we get a valid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        cout << "You have chosen: " << choice << endl;
        
        switch (choice)
        {
        case 1:
            if (player->getCurrentHero() == nullptr) {
                player->setCurrentHero(player->getHero(0));
            }
            if (player->getCurrentHero() != nullptr) {
                SuperHero* target = selectTarget(player);
                if (target != nullptr) {
                    player->getCurrentHero()->attack(*target);
                    validInput = true;
                } else {
                    cout << "No valid target available." << endl;
                }
            } else {
                cout << "No heroes available." << endl;
            }
            break;
            
        case 2:
            {
                cout << "Choose your artefact:" << endl;
                Artefacts* art = selectArtefact(player);
                cout << "do you want to use on your hero or on the enemy?" << endl;
                cout << "1. Use on your hero" << endl;
                cout << "2. Use on the enemy" << endl;
                int artefactChoice;
                cin >> artefactChoice;
                if (artefactChoice == 1) {
                    SuperHero* hero = selectTarget(player);
                    if (hero != nullptr) {
                        art->use(hero);
                        validInput = true;
                    } else {
                        cout << "No heroes available." << endl;
                    }
                } else if (artefactChoice == 2) {
                    SuperHero* target = selectTarget(player);
                    if (target != nullptr) {
                        art->use(target);
                        validInput = true;
                    } else {
                        cout << "No valid target available." << endl;
                    }
                } else {
                    cout << "Invalid choice!" << endl;
                }
                if (art != nullptr) {
                    player->removeArtefact(art);
                    cout << "Artefact " << art->getName() << " used!" << endl;
                } else {
                    cout << "No artefacts available." << endl;
                }
                break;
            }
            
        case 3:
            {
                SuperHero* hero = player->getHero(0);
                if (hero != nullptr) {
                    player->setCurrentHero(hero);
                    cout << "You have switched to " << player->getCurrentHero()->getName() << endl;
                    validInput = true;
                } else {
                    cout << "No heroes available to switch to." << endl;
                }
            }
            break;
            
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }
    
    cout << player->getName() << " action done!" << endl;
}
SuperHero* Game::selectTarget(Player *player)
{
    cout << "Choose your target:" << endl;
    Player *targetPlayer = nullptr;
    
    // Find another player to target
    for (auto &p : player_list)
    {
        if (p != player)
        {
            targetPlayer = p;
            break;
        }
    }
    
    if (targetPlayer == nullptr) {
        cout << "No other players available to target." << endl;
        return nullptr;
    }
    
    return selectHero(targetPlayer);
}


bool Game::checkGameOver(Player *player)
{
    if (player->isTeamAlive() == false)
    {
        cout << "Player " << player->getName() << " is out of the game!" << endl;
        for (int i = 0; i < static_cast<int>((player->getTeam().size())); i++)
        {
            cout << "Removing hero: " << player->getHero(i)->getName() << endl;
            player->removeHero(player->getHero(i));
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
    if (player == nullptr) {
        cout << "Invalid player." << endl;
        return nullptr;
    }
    
    if (player->getTeam().empty()) {
        cout << "Player has no heroes." << endl;
        return nullptr;
    }
    
    cout << "Select a hero:" << endl;
    player->displayTeam();
    int choice;
    cin >> choice;
    
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input." << endl;
        return nullptr;
    }
    
    SuperHero* hero = player->getHero(choice);
    if (hero == nullptr) {
        cout << "Invalid hero selection." << endl;
    }
    return hero;
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

Player* Game::getPlayer(int index)
{
    if (index == 0)
    {
        displayPlayerList();
        cout << "Choose a player:" << endl;
        cin >> index;
    }
    if (index >= 0 && index < static_cast<int>((player_list.size())))
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
