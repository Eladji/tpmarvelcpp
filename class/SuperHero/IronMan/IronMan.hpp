#include "class/SuperHero/SuperHero.hpp"
#pragma once
class IronMan : public SuperHero
{
private:
    /* data */
public:
    IronMan(/* args */);
    void attack(SuperHero& target);
    void specialAttack(SuperHero& target);
};

