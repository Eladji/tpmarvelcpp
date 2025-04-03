#include "Artefacts.cpp"
#pragma once

class HealthPotion : public Artefacts
{
private:
    int healAmount;
public:
    HealthPotion();
    void display() const;
    void use(SuperHero& target);
};
