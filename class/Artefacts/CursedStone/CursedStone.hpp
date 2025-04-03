#include "class/Artefacts/Artefacts.hpp"

class CursedStone : public Artefacts
{
private:
    /* data */
public:
    CursedStone(/* args */);
    void display() const;
    void use(SuperHero& target);
};