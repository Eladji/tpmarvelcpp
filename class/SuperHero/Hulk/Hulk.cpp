#include "Hulk.hpp"

Hulk::Hulk(/* args */):SuperHero("Hulk",200, 200, 30, 100, 20,false)
{
    this->cooldown = 0;
    this->ragetime = 0;
}


void Hulk::attack(SuperHero& target)
{
    if (this->getCooldown() > 0){
        cout << "Hulk est en cooldown" << endl;
        this->setCooldown(this->getCooldown() - 1);
        return;
    }
    else{
    cout << "Hulk attaque " << target.getName() << endl;
    srand(time(0));
    double val = (double)rand() / RAND_MAX;
    if (val < 0.05)    {   //  5%
        cout << "Hulk à louper son attaque" << endl;
        this->recoil();

    }
    else
    {
    target.takeDamage(this->getRagetime() > 0 ? this->CriticalHit() * 2 : this->CriticalHit());
    this->recoil();
    }
}
}
void Hulk::setRagetime(int time = 2){
    this->ragetime = time;
    if (time > 0){
        cout << "Hulk entre en rage ! Ses attaques deviennent incontrôlables !" << endl;
    }
    else {
        cout << "Hulk n'est plus enragé" << endl;
        this->setCooldown(1);
    }
}

int Hulk::getRagetime()const {
    return this->ragetime;
}

int Hulk::getCooldown()const {
    return this->cooldown;
}

void Hulk::setCooldown(int cooldown){
    this->cooldown = cooldown;
}


void Hulk::recoil(){
    cout << "Hulk subit un recul" << endl;
    this->takeDamage(this->getMaxHealthPoints() * 0.05);
}

void Hulk::specialAttack(SuperHero& target){
    if (this->isSpecialAvailable()){
        cout << "Hulk utilise son attaque spéciale sur " << target.getName() << endl;
        target.takeDamage(this->CriticalHit() * 2);
        this->setCooldown(3);
    }
    else {
        cout << "l'attaque spécial n'est pas disponible" << endl;
    }
}

void Hulk::display() const {
    cout << "Cooldown : " << this->getCooldown() << endl;
    cout << "Ragetime : " << this->getRagetime() << endl;
}   