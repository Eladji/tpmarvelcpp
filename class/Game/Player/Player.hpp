#include "SuperHero/Spider/SpiderMan.cpp"
#include "SuperHero/Hulk/Hulk.cpp"
#include "SuperHero/IronMan/IronMan.cpp"
#include "SuperHero/Docteur Strange/DocteurStrange.cpp"
#include "Artefacts/CursedStone/CursedStone.cpp"
#include "Artefacts/HealthPotion/HealthPotion.cpp"
#include "Artefacts/PowerAmulet/PowerAmulet.cpp"
#include <algorithm>
class Player
{
private:
    string name;
    vector<SuperHero> team;
    SuperHero* currentHero;

    vector<Artefacts> inventory;
    Artefacts* currentArtefact;
public:
    Player(string name);
    ~Player();
    void addHero(SuperHero& hero);
    void removeHero(SuperHero& hero);
    void addArtefact(Artefacts& artefact);
    void removeArtefact(Artefacts& artefact);
    void setCurrentHero(SuperHero* hero);
    void setCurrentArtefact(Artefacts* artefact);
    SuperHero* getCurrentHero();
    Artefacts* getCurrentArtefact();
    vector<SuperHero> getTeam();
    vector<Artefacts> getInventory();
    void displayTeam();
    void displayInventory();
    SuperHero* getHero(int index);
    string getName() const;
    void setName(string name);
    bool isTeamAlive() {};
    Artefacts* getArtefact(int index);

};
