#include "SuperHero.hpp"

SuperHero::SuperHero(string name, int hp, int maxHealthPoints, int baseAttack, int maxEnergy, int criticalHit, bool isAoe)
{
    this->name = name;
    this->healthPoints = hp;
    this->baseAttack = baseAttack;
    this->maxHealthPoints = maxHealthPoints;
    this->specialAvailable = false;
    this->maxEnergy = maxEnergy;
    this->energy = 0;
    this->criticalHit = criticalHit;
    this->isAoe = isAoe;
}
SuperHero::~SuperHero()
{
    cout << "SuperHero " << name << " détruit!" << endl;
}
bool SuperHero::isAlive() const {
    return healthPoints > 0;
}

void SuperHero::takeDamage(int damage)
{
    healthPoints -= damage;
    if (healthPoints < 0)
    {
        healthPoints = 0;
    }
    if (healthPoints == 0)
    {
        cout << name << " est battue!" << endl;
    }
    else
    {
        cout << name << " prend " << damage << " dégat!" << endl;
    }
}

void SuperHero::display() const {
    if (!isAlive()) {
        cout << "Name: \033[38;5;208m" << name << "\033[0m (DEFEATED)" << endl;
    } else {
        cout << "Name: " << name << endl;
    }
    cout << "Health: " << healthPoints << "/" << maxHealthPoints << endl;
    cout << "Attack: " << baseAttack << endl;
    cout << "Energy: " << energy << "/" << maxEnergy << endl;
    cout << "Critical Hit Chance: " << criticalHit << endl;
    cout << "Special Attack: " << (specialAvailable ? "Disponible" : "Non Disponible") << endl;
}

void SuperHero::heal(int healAmount)
{
    healthPoints += healAmount;
    if (healthPoints > this->maxHealthPoints)
    {
        healthPoints = this->maxHealthPoints;
    }
}

string SuperHero::getName()
{
    return name;
}

int SuperHero::getHealthPoints()
{
    return healthPoints;
}

int SuperHero::getBaseAttack()
{
    return baseAttack;
}

bool SuperHero::isSpecialAvailable()
{
    return specialAvailable;
}

void SuperHero::setSpecialAvailable(bool specialAvailable)
{
    this->specialAvailable = specialAvailable;
}

void SuperHero::setCriticalHit(int criticalHit)
{
    this->criticalHit = criticalHit;
}

int SuperHero::getCriticalHit()
{
    return criticalHit;
}

void SuperHero::setEnergy(int energy)
{
    this->energy = energy;
    if (energy >= this->maxEnergy)
    {
        this->energy = this->maxEnergy;
        this->specialAvailable = true;
    }
}

int SuperHero::getEnergy()
{
    return energy;
}

int SuperHero::CriticalHit(){
    srand ( time(NULL) );	// seeds rand() with a number based on the current system time.

	if ( this->getCriticalHit() > rand() % 200 )
		return this->getBaseAttack() + this->getBaseAttack() * 0.25 ;
	else
		return this->getBaseAttack();
}

void SuperHero::setMaxEnergy(int maxEnergy)
{
    this->maxEnergy = maxEnergy;
}

int SuperHero::getMaxEnergy()
{
    return maxEnergy;
}
void SuperHero::setMaxHealthPoints(int maxHealthPoints)
{
    this->maxHealthPoints = maxHealthPoints;
}
int SuperHero::getMaxHealthPoints()
{
    return maxHealthPoints;
}
void SuperHero::setBaseAttack(int baseAttack)
{
    this->baseAttack = baseAttack;
}

bool SuperHero::getisAoe() const
{
    return isAoe;
}
void SuperHero::setAoe(bool isAoe)
{
    this->isAoe = isAoe;
}

// Add this to class/SuperHero/SuperHero.cpp
void SuperHero::specialAttack(SuperHero &target) {
    cout << "Ce hero n'a pas d'attaque a cible unique." << endl;
}

void SuperHero::specialAttackAOE(vector<SuperHero*> target) {
    cout << "Ce hero n'a pas d'attaque a cible multiple." << endl;
}

void SuperHero::attack(SuperHero &target) {
    cout << name <<" attaque " << target.getName() << endl;
    srand(time(0));
    double val = (double)rand() / RAND_MAX;
    if (val < 0.05)    {   //  5%
        cout << name <<" a louper son attaque" << endl;
    }
    else if (val < 0.30)   {   //  30%
        cout << name <<" charge son énergie " << target.getName() << endl;
        this->setEnergy(this->getEnergy() + 10);
        target.takeDamage(this->CriticalHit());
    }
    else
    {
     target.takeDamage(this->CriticalHit());
}
}