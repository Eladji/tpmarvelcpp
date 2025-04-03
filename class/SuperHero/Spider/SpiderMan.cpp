#include "SpiderMan.hpp"
#include <math.h>

SpiderMan::SpiderMan(/* args */):SuperHero("SpiderMan", 100, 15, 100, 100, 20)
{
}




void SpiderMan::attack(SuperHero& target)
{
    cout << "SpiderMan attacks " << target.getName() << " with a basic attack" << endl;
    srand(time(0));
    double val = (double)rand() / RAND_MAX;
    int random;
    if (val < 0.05)    {   //  5%
        cout << "SpiderMan missed the attack" << endl;
    }
    else if (val < 0.30)   {   //  30%
        cout << "SpiderMan Spider-Man a immobiliser "<< target.getName() << endl;
        target.takeDamage(this->CriticalHit());
    }
    else
    {
     target.takeDamage(this->CriticalHit());
    }
}

void SpiderMan::specialAttack(SuperHero& target){
    if (this->isSpecialAvailable()){
        cout << "Spider-Man utilise sa toile pour immobiliser " << target.getName() <<" !" << endl; 
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}

