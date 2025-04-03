#include "PowerAmulet.hpp"

PowerAmulet::PowerAmulet(/* args */):Artefacts("Power Amulet", 5)
{
}

void PowerAmulet::display() const
{
    cout << "Power Amulet: " << this->getName() <<", Value: " << this->getValue() << endl;
}
void PowerAmulet::use(SuperHero& target)
{
    cout << "Power Amulet used on " << target.getName() << endl;
    target.setBaseAttack(target.getBaseAttack() + this->getValue());
    cout << "l'attaque de base de "<< target.getName() << "a était augmenter de "<< this->getValue() << endl;
}