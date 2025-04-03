#include "DocteurStrange.hpp"
DocteurStrange::DocteurStrange():SuperHero("Docteur Strange",100, 100, 5, 75, 15)
{
    this->ultcharge = 3;
}

void DocteurStrange::setUltcharge(int ultcharge){
    this->ultcharge = ultcharge;
}
int DocteurStrange::getUltcharge()const {
    return this->ultcharge;
}


void DocteurStrange::attack(SuperHero& target)
{
    cout << "Docteur Strange attaque " << target.getName() << endl;
    srand(time(0));
    double val = (double)rand() / RAND_MAX;
    int random;
    if (val < 0.05)    {   //  5%
        cout << "Docteur Strange missed the attack" << endl;
    }
    else if (val < 0.30)   {   //  30%
        cout << "Docteur Strange charge son énergie " << target.getName() << endl;
        this->setEnergy(this->getEnergy() + 10);
        target.takeDamage(this->CriticalHit());
    }
    else
    {
     target.takeDamage(this->CriticalHit());
    }
}

int DocteurStrange::CriticalHit(){
    srand ( time(NULL) );	// seeds rand() with a number based on the current system time.
    if ( this->getCriticalHit() > rand() % 200 )
        return rand() % 2 * this->getBaseAttack() + this->getBaseAttack() * 0.25 ;
    else
        return rand() % 2 * this->getBaseAttack() ;
}
void DocteurStrange::specialAttackAOE(vector<SuperHero*>& target){
    if (this->isSpecialAvailable()){
        cout << "octor Strange ouvre un portail de soin magique." <<  endl;
        for (int i = 0; i < target.size(); i++){
            if (target[i]->isAlive()){
                target[i]->heal(rand()% 15 + 15);
                cout << target[i]->getName() << " est soigné de 20 points de vie." << endl;
            }
        } 
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}