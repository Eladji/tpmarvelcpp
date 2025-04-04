#include "class/SuperHero/Spider/SpiderMan.hpp"
#include "class/SuperHero/Hulk/Hulk.hpp"
#include "class/SuperHero/IronMan/IronMan.hpp"
#include "class/SuperHero/Docteur_Strange/DocteurStrange.hpp"
#include "class/Artefacts/CursedStone/CursedStone.hpp"
#include "class/Artefacts/HealthPotion/HealthPotion.hpp"
#include "class/Artefacts/PowerAmulet/PowerAmulet.hpp"
#include <algorithm>
class Player
{
private:
    string name;
    vector<SuperHero*> team;
    SuperHero* currentHero;

    vector<Artefacts*> inventory;
    Artefacts* currentArtefact;
public:
    Player(string name);
    ~Player();
    void addHero(SuperHero* hero);
    void removeHero(SuperHero* hero);
    void addArtefact(Artefacts* artefact);
    void removeArtefact(Artefacts* artefact);
    void setCurrentHero(SuperHero* hero);
    void setCurrentArtefact(Artefacts* artefact);
    SuperHero* getCurrentHero();
    Artefacts* getCurrentArtefact();
    vector<SuperHero*> getTeam();
    vector<Artefacts*> getInventory();
    void displayTeam();
    void displayInventory();
    SuperHero* getHero(int index);
    string getName() const;
    void setName(string name);
    bool isTeamAlive();
    Artefacts* getArtefact(int index);

};
