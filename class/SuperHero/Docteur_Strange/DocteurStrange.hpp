#include "class/SuperHero/SuperHero.hpp"
#include <vector>
#pragma once
class DocteurStrange : public SuperHero
{
private:
    int ultcharge;
public:
    DocteurStrange();
    void attack(SuperHero& target);
    int CriticalHit();
    void specialAttackAOE(vector<SuperHero*> target); 
    void setUltcharge(int ultcharge);
    int getUltcharge()const;
};