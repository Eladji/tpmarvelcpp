#include <string>
#include <iostream>
#pragma once 
using namespace std;
class SuperHero
{
protected:
    string name;
    int healthPoints;
    int baseAttack;
    bool specialAvailable;
    int maxHealthPoints;
    int criticalHit;
    int energy;
    int maxEnergy;
public:
    SuperHero(string name, int hp, int maxHealthPoints, int baseAttack, int maxEnergy, int criticalHit);
    virtual ~SuperHero();
    virtual void display() const; 
    virtual void attack(SuperHero& target)=0;
    virtual void specialAttack(SuperHero& target) = 0;
    virtual int CriticalHit();
    bool isAlive();
    void takeDamage(int damage);
    void heal(int healAmount);   
    string getName();
    int getHealthPoints();
    int getBaseAttack();
    bool isSpecialAvailable();
    void setSpecialAvailable(bool specialAvailable);
    void setCriticalHit(int criticalHit);
    int getCriticalHit();
    void setEnergy(int energy);
    int getEnergy();
    void setMaxEnergy(int maxEnergy);
    int getMaxEnergy();
    void setMaxHealthPoints(int maxHealthPoints);
    int getMaxHealthPoints();
    void setBaseAttack(int baseAttack);
};
