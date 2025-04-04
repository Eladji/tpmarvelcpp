#include "class/SuperHero/SuperHero.hpp"
#pragma once
class Hulk : public SuperHero
{
private:
    int cooldown;
    int ragetime;

public:
    Hulk(/* args */);
    void attack(SuperHero &target);
    void specialAttack(SuperHero &target);
    void display() const;
    void recoil();
    void setCooldown(int cooldown);
    int getCooldown() const;
    void setRagetime(int time);
    int getRagetime() const;
};