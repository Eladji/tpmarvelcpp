#include "IronMan.hpp"

IronMan::IronMan(/* args */):SuperHero("IronMan", 100, 20, 100, 100, 20,true)
{}



void IronMan::specialAttack(SuperHero& target){
    if (this->isSpecialAvailable()){
        cout << "Iron Man déclenche une salve de missiles sur " << target.getName() <<" !" << endl; 
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}

void IronMan::specialAttackAOE(vector<SuperHero*> target){
    if (this->getStunTime() > 0){
        cout << "Iron man est étourdi et ne peut pas attaquer!" << endl;
        return;
    }
    if (this->isSpecialAvailable()){
        cout << "Iron Man déclenche une salve de missiles sur l'équipe adverse." <<  endl;
        for (int i = 0; i < static_cast<int>((target.size())); i++){
            if (target[i]->isAlive()){
                target[i]->takeDamage(15);
                cout << target[i]->getName() << " est soigné de 20 points de vie." << endl;
            }
        } 
        this->setSpecialAvailable(false);
        this->setEnergy(0);
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}