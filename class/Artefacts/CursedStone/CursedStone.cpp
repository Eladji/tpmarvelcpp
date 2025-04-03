#include "CursedStone.hpp"

CursedStone::CursedStone(/* args */):Artefacts("Cursed Stone", 5)
{
}
void CursedStone::display() const
{
    cout << "Cursed Stone: " << this->getName() <<", Value: " << this->getValue() << endl;
}

void CursedStone::use(SuperHero& target)
{
    cout << "Cursed Stone a était utiliser sur " << target.getName() << endl;
    target.setBaseAttack(target.getBaseAttack() - this->getValue());
    target.setMaxHealthPoints(target.getMaxHealthPoints() - this->getValue());
    target.takeDamage(this->getValue());
    cout << "l'attaque de base de "<< target.getName() << "a était diminuer de "<< this->getValue() << endl;
    cout << "les points de vie Max de "<< target.getName() << "a était diminuer de "<< this->getValue() << endl;
}