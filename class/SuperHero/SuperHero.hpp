#include <string>
#include <iostream>
#include <vector>
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
    bool isAoe;

public:
    SuperHero(string name, int hp, int maxHealthPoints, int baseAttack, int maxEnergy, int criticalHit, bool isAoe = false);
    virtual ~SuperHero();
    virtual void display() const;
    virtual void attack(SuperHero &target) = 0;
    virtual void specialAttack(SuperHero &target);
    virtual int CriticalHit();
    bool isAlive() const;
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
    bool getisAoe() const;
    void setAoe(bool isAoe);
    virtual void specialAttackAOE(vector<SuperHero*> target); 
};
