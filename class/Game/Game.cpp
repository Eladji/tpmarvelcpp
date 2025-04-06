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
        cout << "Player " << player->getName() << " created!" << endl;
        createteam(player);
        player_list.push_back(player);
        if (player_list[i]->getTeam().empty())
        {
            cout << "something went wrong :(" << endl;
            delete player;
            i--;
            continue;
        }
        cout << "Player " << player->getName() << " created!" << endl;
    }
}
void Game::clearTerminal()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/Mac
#endif
    cout << "Terminal cleared!" << endl;
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
    player->setCurrentHero(player->getHero(0));
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

    // Each player takes one action
    for (auto player : player_list)
    {
        checkGameOver();
        if (game_over)
        {
            break;
        }
        action(player);
    }

    setTurn(getTurn() + 1);

    // Clear terminal at end of complete turn
    clearTerminal();
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

    while (!validInput)
    {
        cout << "Player " << player->getName() << "'s turn!" << endl;
        cout << "Current Hero: " << (player->getCurrentHero() ? player->getCurrentHero()->getName() : "None") << endl;

        // Show current hero stats
        if (player->getCurrentHero())
        {
            player->getCurrentHero()->display();
        }

        cout << "Choose your action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use Artefact" << endl;
        cout << "3. Switch Hero" << endl;
        if (player->getCurrentHero() != nullptr && player->getCurrentHero()->isSpecialAvailable())
        {
            cout << "4. Use Special Attack" << endl;
        }
        else
        {
            cout << "4. Charge Energy" << endl;
        }
        cout << "5. Skip Turn" << endl;

        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        cout << "You have chosen: " << choice << endl;

        switch (choice)
        {
        case 1:
            if (player->getCurrentHero() == nullptr)
            {
                player->setCurrentHero(player->getHero(0));
            }
            if (player->getCurrentHero() != nullptr)
            {
                SuperHero *target = selectTarget(player);
                if (target != nullptr)
                {
                    player->getCurrentHero()->attack(*target);
                    validInput = true;
                }
                else
                {
                    cout << "No valid target available." << endl;
                }
            }
            else
            {
                cout << "No heroes available." << endl;
            }
            break;

        case 2:
        {
            cout << "Choose your artefact:" << endl;
            Artefacts *art = selectArtefact(player);
            cout << "do you want to use on your hero or on the enemy?" << endl;
            cout << "1. Use on your hero" << endl;
            cout << "2. Use on the enemy" << endl;
            int artefactChoice;
            cin >> artefactChoice;
            if (artefactChoice == 1)
            {
                SuperHero *hero = selectHero(player);
                if (hero != nullptr)
                {
                    art->use(hero);
                    validInput = true;
                }
                else
                {
                    cout << "No heroes available." << endl;
                }
            }
            else if (artefactChoice == 2)
            {
                SuperHero *target = selectTarget(player);
                if (target != nullptr)
                {
                    art->use(target);
                    validInput = true;
                }
                else
                {
                    cout << "No valid target available." << endl;
                }
            }
            else
            {
                cout << "Invalid choice!" << endl;
            }
            if (art != nullptr)
            {
                player->removeArtefact(art);
                cout << "Artefact " << art->getName() << " used!" << endl;
            }
            else
            {
                cout << "No artefacts available." << endl;
            }
            action(player);
            break;
        }

        case 3:
        {
            SuperHero *hero = selectHero(player);
            if (hero == player->getCurrentHero())
            {
                cout << "You are already using this hero!" << endl;
            }
            else if (hero == nullptr)
            {
                cout << "No heroes available." << endl;
            }
            else
            {
                player->setCurrentHero(hero);
                cout << "You have switched to " << player->getCurrentHero()->getName() << endl;
            }
            break;
        }
        case 4:
        {
            if (player->getCurrentHero() != nullptr)
            {
                if (player->getCurrentHero()->isSpecialAvailable())
                {
                    if (player->getCurrentHero()->getisAoe())
                    {
                        player->getCurrentHero()->specialAttackAOE(player->getTeam()); // this is bad i should have done a getplayer function to select team target so any hero created later with aoe work out of the box but no :) my laptop as 13% battery
                    }
                    else
                    {
                        SuperHero *target = selectTarget(player);
                        if (target != nullptr)
                        {

                            player->getCurrentHero()->specialAttack(*target);

                            validInput = true;
                            cout << "Special attack used!" << endl;
                            target = nullptr;
                        }
                        else
                        {
                            cout << "No valid target available." << endl;
                        }
                    }
                }
                else
                {
                    SuperHero *selectedHero = selectHero(player);
                    selectedHero->setEnergy(selectedHero->getEnergy() + 75);
                    cout << "Energy charging!" << endl;
                    validInput = true;
                }
            }
            else
            {
                cout << "No heroes available." << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Turn skipped!" << endl;
            validInput = true;
            break;
        }
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    }

    cout << player->getName() << "'s action completed!" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); // Wait for Enter key
}

SuperHero *Game::selectTarget(Player *player)
{
    Player *targetPlayer = nullptr;
    if (nb_players == 2)
    {
        // Find another player to target
        for (auto &p : player_list)
        {
            if (p != player)
            {
                targetPlayer = p;
                break;
            }
        }
    }
    else if (nb_players > 3)
    {
        cout << "Choose a target player:" << endl;
        for (int i = 0; i < nb_players; i++)
        {
            if (player_list[i] != player)
            {
                cout << i << ": " << player_list[i]->getName() << endl;
            }
        }
        int choice;
        cin >> choice;
        if (choice >= 0 && choice < nb_players && player_list[choice] != player)
        {
            targetPlayer = player_list[choice];
        }
        else
        {
            cout << "Invalid choice!" << endl;
            return nullptr;
        }
    }
    else if (nb_players == 1)
    {
        cout << "No other players available to target." << endl;
        return nullptr;
    }
    if (targetPlayer == nullptr)
    {
        cout << "No other players available to target." << endl;
        return nullptr;
    }

    return selectHero(targetPlayer);
}

void Game::checkGameOver()
{
    // Check if any player has lost before starting new turn
    vector<Player *> playersToRemove;
    for (auto player : player_list)
    {
        if (!player->isTeamAlive())
        {
            cout << "Player " << player->getName() << " is out of the game!" << endl;
            playersToRemove.push_back(player);
        }
    }

    // Remove eliminated players
    for (auto player : playersToRemove)
    {
        removePlayer(player);
    }

    // If only one player remains after removing others, they win
    if (player_list.size() <= 1)
    {
        if (player_list.size() == 1)
        {
            displayWinner(player_list[0]);
        }
        endGame();
        game_over = true;
        return;
    }
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
    if (player == nullptr)
    {
        cout << "Invalid player." << endl;
        return nullptr;
    }

    if (player->getTeam().empty())
    {
        cout << "Player has no heroes." << endl;
        return nullptr;
    }

    cout << "Select a hero:" << endl;
    player->displayTeam();
    int choice;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input." << endl;
        return nullptr;
    }

    SuperHero *hero = player->getHero(choice);
    if (hero == nullptr)
    {
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
        cout << "Player " << player->getName() << " removed!" << endl;
        // delete player;
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

Player *Game::getPlayer(int index)
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
