#include "class/SuperHero/SuperHero.hpp"
#pragma once
class IronMan : public SuperHero
{
private:
    /* data */
public:
    IronMan(/* args */);
    void specialAttack(SuperHero& target);
    void specialAttackAOE(vector<SuperHero*> target);
};

