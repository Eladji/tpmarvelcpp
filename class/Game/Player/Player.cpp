#include "Player.hpp"

Player::Player(string name) {
    this->name = name;
    this->currentHero = nullptr;
    this->currentArtefact = nullptr;
}
Player::~Player() {
    for (auto hero : team) {
        delete hero;
    }
    for (auto art : inventory) {
        delete art;
    }
}
void Player::addHero(SuperHero* hero) {
    team.push_back(hero);
}
void Player::removeHero(SuperHero* hero) {
    auto it = find(team.begin(), team.end(), hero);
    if (it != team.end()) {
        team.erase(it);
    }
}
void Player::addArtefact(Artefacts* artefact) {
    inventory.push_back(artefact);
}
void Player::removeArtefact(Artefacts* artefact) {
    auto it = find(inventory.begin(), inventory.end(), artefact);
    if (it != inventory.end()) {
        inventory.erase(it);
    }   
}

void Player::setCurrentHero(SuperHero* hero) {
    this->currentHero = hero;
}
void Player::setCurrentArtefact(Artefacts* artefact) {
    this->currentArtefact = artefact;
}
SuperHero* Player::getCurrentHero() {
    return currentHero;
}
Artefacts* Player::getCurrentArtefact() {
    return currentArtefact;
}
vector<SuperHero*> Player::getTeam() {
    return team;
}
vector<Artefacts*> Player::getInventory() {
    return inventory;
}
void Player::displayTeam() {
    cout << "Team: " << endl;
    for (size_t i = 0; i < team.size(); i++) {
        cout << i << ": " << team[i]->getName() << " | HP: " << team[i]->getHealthPoints() << " | Attack: " <<team[i]->getBaseAttack()<< "  ";
    }
    cout << endl;
    cout << "Current Hero: " << (currentHero ? currentHero->getName() : "None") << endl;
}
void Player::displayInventory() {
    cout << "Inventory: " << endl;
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i << ": " << inventory[i]->getName() << endl;
    }
}
SuperHero* Player::getHero(int index) {
    // The condition is completely wrong - missing comparison operator between index and team.size()
    // Change from:
    // if (index < 0 || static_cast<int>(team.size())) {
    
    // To proper bounds checking:
    if (index < 0 || index >= static_cast<int>(team.size())) {
        cout << "Index out of range" << endl;
        return nullptr;
    }
    return team[index];
}

string Player::getName() const {
    return name;
}
void Player::setName(string name) {
    this->name = name;
}

bool Player::isTeamAlive() {
    bool isAlive = true;
    int count = 0;
    for (auto* hero : team) {
        if (!hero->isAlive()) {
            count++;
            break;
        }
        if(count == static_cast<int>(team.size())) {
            isAlive = false;
        }
    }
    return isAlive;
}
Artefacts* Player::getArtefact(int index) {
    // Fix the same issue here
    if (index < 0 || index >= static_cast<int>(inventory.size())) {
        return nullptr;
    }
    return inventory[index];
}