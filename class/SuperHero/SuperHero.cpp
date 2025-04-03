#include "SuperHero.hpp"

SuperHero::SuperHero(string name, int hp, int maxHealthPoints, int baseAttack, int maxEnergy, int criticalHit)
{
    this->name = name;
    this->healthPoints = hp;
    this->baseAttack = baseAttack;
    this->maxHealthPoints = maxHealthPoints;
    this->specialAvailable = false;
    this->maxEnergy = maxEnergy;
    this->energy = 0;
    this->criticalHit = criticalHit;
}

bool SuperHero::isAlive()
{
    return healthPoints > 0;
}

void SuperHero::takeDamage(int damage)
{
    healthPoints -= damage;
    if (healthPoints < 0)
    {
        healthPoints = 0;
    }
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
