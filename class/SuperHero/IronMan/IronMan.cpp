#include "IronMan.hpp"

IronMan::IronMan(/* args */):SuperHero("IronMan", 100, 20, 100, 100, 20,false)
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
    if (this->isSpecialAvailable()){
        cout << "Iron Man déclenche une salve de missiles sur l'équipe adverse." <<  endl;
        for (int i = 0; i < static_cast<int>((target.size())); i++){
            if (target[i]->isAlive()){
                target[i]->takeDamage(15);
                cout << target[i]->getName() << " est soigné de 20 points de vie." << endl;
            }
        } 
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}