#include <iostream>
#include <memory>

#include "World.h"


int main() {

    World world;

    world.addEntity(std::make_unique<Player>("", Faction::OLD_CAMP, 100, 20, std::make_unique<Paladin>()));
    world.addEntity(std::make_unique<NPC>("Lothar", Faction::OLD_CAMP, AI::ALLY, 150, 100, std::make_unique<Paladin>()));
    world.addEntity(std::make_unique<NPC>("Gorn", Faction::NEW_CAMP, AI::ALLY, 200, 20, std::make_unique<DragonHunter>()));


    for (auto it = world.entityTypeIterator(EntityType::NPC); it != world.end(); ++it) { // Zwiększamy dawkę odtrutki :)
        it->debugInfo();
    }

    world.clear();
}

/*

Dodajemy nowe statystyki, które klasy łączone dziedziczą jako sumę.

Warrior:

    Strength: 50
    Dexterity: 20
    Armor: 50

Archer:

    Strength: 20
    Dexterity: 50
    Armor: 30

Mage:

    Strength: 10
    Dexterity: 10
    Armor: 5


Paladin = Warrior + Mage
Dragon Hunter = Warrior + Archer

Mają być diamenty! :)


Oczekiwany output

AI:

    EntityID: 1
    Name: Lothar
    Faction: Old Camp
    AI: Ally
    Health: 150
    Mana: 100
    Class: Paladin
    Strength: 60        // 50 + 10
    Dexterity: 30       // 20 + 10
    Armor: 55           // 50 + 5

AI:

    EntityID: 2
    Name: Gorn
    Faction: New Camp
    AI: Ally
    Health: 200
    Mana: 20
    Class: Dragon Hunter
    Strength Bonus: 70      // 50 + 20
    Dexterity Bonus: 70     // 20 + 50
    Armor Bonus: 80         // 50 + 30

*/
