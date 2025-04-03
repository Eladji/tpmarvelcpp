#include "HealthPotion.hpp"

HealthPotion::HealthPotion():Artefacts(name, healAmount)
{
}

void HealthPotion::use(SuperHero& target)
{
    cout << "Une potion de Heal a était utiliser sur " << target.getName() << endl;
    target.heal(healAmount);
    cout << target.getName() << " a était soigner pour  " << healAmount << " points de." << endl;
    delete this; // Assuming the potion is consumed after use
}

void HealthPotion::display() const
{
    cout << "Health Potion: " << this->getName() <<", Heal Amount: " << this->getValue() << endl;
}