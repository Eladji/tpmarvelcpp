#include "SuperHero.hpp"
#pragma once
class IronMan : public SuperHero
{
private:
    /* data */
public:
    IronMan(/* args */);
    ~IronMan();
    void attack(SuperHero& target);
    void specialAttack(SuperHero& target);
    int CriticalHit();
    void display() const;
};

