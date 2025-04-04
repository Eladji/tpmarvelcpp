#include "IronMan.hpp"

IronMan::IronMan(/* args */):SuperHero("IronMan", 100, 20, 100, 100, 20)
{}

void IronMan::attack(SuperHero& target)
{
    cout << "IronMan attaque " << target.getName() << endl;
    srand(time(0));
    double val = (double)rand() / RAND_MAX;
    if (val < 0.05)    {   //  5%
        cout << "IronMan missed the attack" << endl;
    }
    else if (val < 0.30)   {   //  30%
        cout << "IronMan immobilise " << target.getName() << endl;
        target.takeDamage(this->CriticalHit());
    }
    else
    {
     target.takeDamage(this->CriticalHit());
    }
}

void IronMan::specialAttack(SuperHero& target){
    if (this->isSpecialAvailable()){
        cout << "ron Man déclenche une salve de missiles sur " << target.getName() <<" !" << endl; 
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}