#include "SpiderMan.hpp"
#include <math.h>

SpiderMan::SpiderMan(/* args */):SuperHero("SpiderMan", 100, 100, 100, 100, 20,false)
{
}

void SpiderMan::attack(SuperHero& target)
{
    cout << "SpiderMan attaque " << target.getName() << " avec une attaque basique" << endl;
    srand(time(0));
    double val = (double)rand() / RAND_MAX;
    if (val < 0.05)    {   //  5%
        cout << "SpiderMan a louper son attaque" << endl;
    }
    else if (val < 0.30)   {   //  30%
        cout << "SpiderMan Spider-Man a immobiliser "<< target.getName() << endl;
        target.takeDamage(this->CriticalHit());
        this->setEnergy(this->getEnergy() + 10);
        cout << "SpiderMan a gagné 10 points d'énergie" << endl;
        target.setStunTime(2);
        cout << target.getName() << " est immobilisé pendant 2 tours" << endl;
    }
    else
    {
     target.takeDamage(this->CriticalHit());
    }
}

void SpiderMan::specialAttack(SuperHero& target){
    if (this->isSpecialAvailable()){
        target.setStunTime(2);
        this->setSpecialAvailable(false);
        this->setEnergy(0);
        cout << "Spider-Man utilise sa toile pour immobiliser " << target.getName() <<" !" << endl; 
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}

