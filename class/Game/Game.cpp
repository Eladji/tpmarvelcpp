#include "Game.hpp"
#include <chrono>
#include <thread>

Game::Game()
{
    this->turn = 0;

    cout << "Entre le nombres de joueur: ";
    cin >> this->nb_players;
    this->game_over = false;
    cout << "Partie créé!" << endl;
    cout << "Nombre de joueurs: " << this->nb_players << endl;
    cout << "La partie commenceras dans :" << endl;
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
    cout << "Partie détruite!" << endl;
}

void Game::startGame()
{
    cout << "Partie lancer!" << endl;
    createPlayer();
    setTurn(1);
    while (!game_over)
    {
        nextTurn();
    }
}
void Game::createPlayer()
{
    for (int i = 0; i < this->nb_players; i++)
    {
        cout << "Joueur " << i  + 1 << " Entre vôtre nom: ";
        string name;
        cin >> name;
        Player *player = new Player(name);
        createteam(player);
        player_list.push_back(player);
        if (player_list[i]->getTeam().empty())
        {
            cout << "nah gros comment t'as fait :(" << endl;
            delete player;
            i--;
            continue;
        }
        cout << "Joeur " << player->getName() << " créé!" << endl;
    }
}
void Game::clearTerminal()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/Mac
#endif
    cout << "Terminal nettoyer!" << endl;
}

void Game::createteam(Player *player)
{
    cout << "Choisissez vôtre équipe:" << endl;
    int choice;
    for (int i = 0; i < 4; i++)
    {
        cout << "1. Hulk" << endl;
        cout << "2. Spider Man" << endl;
        cout << "3. Iron Man" << endl;
        cout << "4. Doctor Strange" << endl;

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
            cout << "choix invalide!" << endl;
            i--;
            continue;
        }
        cout << "Hero " << player->getHero(i)->getName() << " créé!" << endl;
    }
    player->setCurrentHero(player->getHero(0));
    cout << "equipe créé!" << endl;
    player->displayTeam();
    cout << "choisissez vôtre artefacts:" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "1. Cursed Stone" << endl;
        cout << "2. Health Potion" << endl;
        cout << "3. Power Amulet" << endl;
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
            cout << "choix invalide!" << endl;
            i--;
            continue;
        }
        }
        cout << "Artefact " << player->getArtefact(i)->getName() << " créé!" << endl;
    }
    cout << "Inventaire completé!" << endl;
    player->displayInventory();
}

void Game::endGame()
{
    cout << "Partie finit!" << endl;
}

void Game::nextTurn()
{
    displayTurn();
    // Each player takes one action
    for (auto player : player_list)
    {
        checkGameOver();
        if (game_over)
        {
            break;
        }
        action(player);
        for (auto hero : player->getTeam())
        {
            hero->setCD(hero->getCD() - 1);

            if (player->getCurrentHero()->isStunned())
            {
                cout << player->getCurrentHero()->getName() << " est étourdi et ne peut pas agir!" << endl;
              
            }
        }
        
    }

    setTurn(getTurn() + 1);

    // Clear terminal at end of complete tour
    clearTerminal();
}
void Game::displayTurn()
{
    cout << "Tour: " << turn << endl;
}
void Game::displayWinner(Player *player)
{
    cout << "Joueur " << player->getName() << " a gagner!" << endl;
}
void Game::setTurn(int tour)
{
    this->turn = tour;
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
        cout << "Tour de  " << player->getName() << "!" << endl;
        cout << " Hero actuel: " << (player->getCurrentHero() ? player->getCurrentHero()->getName() : "None") << endl;

        // Show current hero stats
        if (player->getCurrentHero())
        {
            player->getCurrentHero()->display();
        }

        cout << "Choisissez vôtre action:" << endl;
        cout << "1. Attaque" << endl;
        cout << "2. Utiliser un Artefact" << endl;
        cout << "3. changer de hero" << endl;
        if (player->getCurrentHero() != nullptr && player->getCurrentHero()->isSpecialAvailable())
        {
            cout << "4. Utiliser une attaque spécial" << endl;
        }
        else
        {
            cout << "4. charger l'énergie" << endl;
        }
        cout << "5. passer son tour" << endl;

        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entré invalide. entré un chiffre." << endl;
            continue;
        }

        cout << "Vous avez choisit: " << choice << endl;

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
                    cout << "Pas de cible valide." << endl;
                }
            }
            else
            {
                cout << "Pas de hero disponible." << endl;
            }
            break;

        case 2:
        {
            cout << "Choisissez vôtre artefact:" << endl;
            Artefacts *art = selectArtefact(player);
            cout << "voulez vous l'utiliser sur un de vos hero ou celui d'un adversaire ?" << endl;
            cout << "1. Utiliser sur vôtre hero" << endl;
            cout << "2. Use Utiliser sur un hero adverse" << endl;
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
                    cout << "Pas de hero disponible." << endl;
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
                    cout << "Pas de cible Disponible." << endl;
                }
            }
            else
            {
                cout << "Choix invalide!" << endl;
            }
            if (art != nullptr)
            {
                player->removeArtefact(art);
                cout << "Artefact " << art->getName() << " Utiliser!" << endl;
            }
            else
            {
                cout << "Pas artefacts disponible." << endl;
            }
            action(player);
            break;
        }

        case 3:
        {
            SuperHero *hero = selectHero(player);
            if (hero == player->getCurrentHero())
            {
                cout << "Vous utilise déja se hero!" << endl;
            }
            else if (hero == nullptr)
            {
                cout << "Pas de hero disponible." << endl;
            }
            else
            {
                player->setCurrentHero(hero);
                cout << "Vous avez changer pour " << player->getCurrentHero()->getName() << endl;
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
                        player->getCurrentHero()->specialAttackAOE(getPlayer()->getTeam()); // this is bad i should have done a getplayer function to select team target so any hero created later with aoe work out of the box but no :) my laptop as 13% battery update i did it
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
                    cout << "L'energie de " << selectedHero->getName() << " ce charge"<<" !" << endl;
                    validInput = true;
                }
            }
            else
            {
                cout << "Pas de hero de disponible." << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Tour passer!" << endl;
            validInput = true;
            break;
        }
        default:
            cout << "choix invalide." << endl;
            break;
        }
    }

    cout << player->getName() << "'s action finit !" << endl;
    cout << "Presser Entre pour continue..." << endl;
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
        cout << "Choisissez un joeur a cibler:" << endl;
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
            cout << "Choix invalide!" << endl;
            return nullptr;
        }
    }
    else if (nb_players == 1)
    {
        cout << "il n'y a pas de joeur à ciblé." << endl;
        return nullptr;
    }
    if (targetPlayer == nullptr)
    {
        cout << "il n'y a pas de joeur à ciblé." << endl;
        return nullptr;
    }

    return selectHero(targetPlayer);
}

void Game::checkGameOver()
{
    // Check if any player has lost before starting new tour
    vector<Player *> playersToRemove;
    for (auto player : player_list)
    {
        if (!player->isTeamAlive())
        {
            cout << "Joueur " << player->getName() << " est hors jeux!" << endl;
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
    cout << "Choisissez un  artefact:" << endl;
    int choice;
    cin >> choice;
    return player->getArtefact(choice);
}
SuperHero *Game::selectHero(Player *player)
{
    if (player == nullptr)
    {
        cout << "Joueur invalide." << endl;
        return nullptr;
    }

    if (player->getTeam().empty())
    {
        cout << "Le joueur n'as pas de hero." << endl;
        return nullptr;
    }

    cout << "Choisissez un hero:" << endl;
    player->displayTeam();
    int choice;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entré invalide." << endl;
        return nullptr;
    }

    SuperHero *hero = player->getHero(choice);
    if (hero == nullptr)
    {
        cout << "Hero selectionner invalide." << endl;
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
        cout << "Joueur " << player->getName() << " retirer!" << endl;
        // delete player;
    }
}
void Game::displayPlayerList()
{
    cout << "Liste de Joueurs:" << endl;
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
        cout << "Choisissez un joueur:" << endl;
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
    cout << "Liste de Joueurs:" << endl;
    for (auto player : player_list)
    {
        cout << player->getName() << endl;
    }
}
