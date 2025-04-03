#include "class/Artefacts/Artefacts.hpp"

class PowerAmulet : public Artefacts
{
private:
    /* data */
public:
    PowerAmulet(/* args */);
    void display() const;
    void use(SuperHero& target);
};
