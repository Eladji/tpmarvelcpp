#include <string>
#include <iostream>
#include "class/SuperHero/SuperHero.hpp"
#pragma once 
using namespace std;

class Artefacts
{
protected:
    string name;
    int value; // value of the artefact
public:
    Artefacts(string name, int value);
    virtual ~Artefacts();
    virtual void display() const = 0;
    virtual void use(SuperHero* target) = 0;
    void setName(string name);
    string getName() const;
    void setValue(int value);
    int getValue() const;

};

