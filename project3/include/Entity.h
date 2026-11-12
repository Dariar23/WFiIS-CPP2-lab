#pragma once
#include <iostream>
#include <string>
#include<memory>
#include "Faction.h"
#include "AI.h"
#include "Class.h"

class Entity{
    //world.addEntity(std::make_unique<Player>("", Faction::NEW_CAMP, 100, 20, std::make_unique<Warrior>()));
    protected:
    static int _id;
    std::string _name;
    Faction _faction;
    
    public:
    Entity(std::string name, Faction faction): _name(name), _faction(faction){}
    virtual ~Entity() = default;
    virtual void debugInfo() const;
    
};
class Player: public Entity{
    private:
    int _health;
    int _mana;
    std::unique_ptr<Class> _class;
    public:
    Player(const std::string &name , Faction fraction, int health, int mana, std::unique_ptr<Class> cl ): Entity(name, fraction), _health(health), _mana(mana), _class(std::move(cl)){}
    void debugInfo() const override{
        std::cout << "Player:" << std::endl;
        std::cout << "    EntityID: " << _id << std::endl;
        std::cout << "    Name: " << _name << std::endl;
        std::cout << "    Faction: " << factionToString(_faction) << std::endl;
        std::cout << "    Health: " << _health << std::endl;
        std::cout << "    Mana: " << _mana << std::endl;
        std::cout << "    Class: " << _class->getClassName() << std::endl;
    }


};
class NPC: public Entity{
    private:
    AI _ai;
    int _health;
    int _mana;
    std::unique_ptr<Class> _class;
    public:
    NPC(const std::string &name , Faction fraction, AI ai,int health, int mana, std::unique_ptr<Class> cl ): Entity(name, fraction), _ai(ai), _health(health), _mana(mana), _class(std::move(cl)){}
    void debugInfo() const override{
        std::cout << "AI:" << std::endl;
        std::cout << "    EntityID: " << _id << std::endl;
        std::cout << "    Name: " << _name << std::endl;
        std::cout << "    Faction: " << factionToString(_faction) << std::endl;
        std::cout << "    Health: " << _health << std::endl;
        std::cout << "    Mana: " << _mana << std::endl;
        std::cout << "    Class: " << _class->getClassName() << std::endl;
    }


};
class Tree: public Entity{
    public:
    Tree(const std::string& name): Entity(name, Faction::NONE){}
    void debugInfo() const override{
        std::cout << "Tree:" << std::endl;
        std::cout << "    EntityID: " << _id << std::endl;
        std::cout << "    Name: " << _name << std::endl;
    }

};
// AI:

//     EntityID: 1
//     Name: Milten 
//     Faction: Old Camp
//     AI: Neutral
//     Health: 20
//     Mana: 100
//     Class: Mage