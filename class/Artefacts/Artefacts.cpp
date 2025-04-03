#include "Artefacts.hpp"

Artefacts::Artefacts(string name, int value)
{
    this->name = name;
    this->value = value;
}
Artefacts::~Artefacts()
{
}
void Artefacts::display() const
{
    cout << "Artefact: " << name << ", Value: " << value << endl;
}
void Artefacts::use(SuperHero* &target)
{
    cout << "Using artefact on " << target->getName() << endl;
}
void Artefacts::setName(string name)
{
    this->name = name;
}
string Artefacts::getName() const
{
    return this->name;
}
void Artefacts::setValue(int value)
{
    this->value = value;
}
int Artefacts::getValue() const
{
    return this->value;
}