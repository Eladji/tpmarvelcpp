
#include "class/SuperHero/SuperHero.hpp"
#pragma once 

class SpiderMan :public SuperHero
{
private:
    /* data */
public:
    SpiderMan(/* args */);
    ~SpiderMan();
    void attack(SuperHero& target);
    void specialAttack(SuperHero& target);
    int CriticalHit();
    void display() const;
};




