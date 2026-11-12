#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Faction.h"
#include "Class.h"
#include "AI.h"

class Entity {
    protected:
    std::string _name;
    Faction _faction;
    static int _nextId;
    int _id;
    public:
    virtual ~Entity() = default;
    Entity(const std::string& n, Faction f) : _name(n), _faction(f), _id(_nextId++) {}
    virtual void debugInfo() const = 0;
};

class Player : public Entity {
    private:
    int _health;
    int _mana;
    std::unique_ptr<Class> _class;
    public:
    Player(const std::string &name, Faction fraction, int health, int mana, std::unique_ptr<Class> cl) 
        : Entity(name, fraction), _health(health), _mana(mana), _class(std::move(cl)) {}
    
    void debugInfo() const override {
        std::cout << "Player:" << std::endl;
        std::cout << "    EntityID: " << _id << std::endl;
        std::cout << "    Name: " << _name << std::endl;
        std::cout << "    Faction: " << factionToString(_faction) << std::endl;
        std::cout << "    Health: " << _health << std::endl;
        std::cout << "    Mana: " << _mana << std::endl;
        std::cout << "    Class: " << _class->getName() << std::endl;
        std::cout << "    Strength: " << _class->getStrength() << std::endl;
        std::cout << "    Dexterity: " << _class->getDexterity() << std::endl;
        std::cout << "    Armor: " << _class->getArmor() << std::endl;
    }
};

class NPC : public Entity {
    private:
    AI _type;
    int _health;
    int _mana;
    std::unique_ptr<Class> _class;
    public:
    NPC(const std::string& name, Faction fraction, AI type, int health, int mana, std::unique_ptr<Class> cl) 
        : Entity(name, fraction), _type(type), _health(health), _mana(mana), _class(std::move(cl)) {}
    
    void debugInfo() const override {
        std::cout << "AI:" << std::endl;
        std::cout << "    EntityID: " << _id << std::endl;
        std::cout << "    Name: " << _name << std::endl;
        std::cout << "    Faction: " << factionToString(_faction) << std::endl;
        std::cout << "    AI: " << aiToString(_type) << std::endl;
        std::cout << "    Health: " << _health << std::endl;
        std::cout << "    Mana: " << _mana << std::endl;
        std::cout << "    Class: " << _class->getName() << std::endl;
        std::cout << "    Strength: " << _class->getStrength() << std::endl;
        std::cout << "    Dexterity: " << _class->getDexterity() << std::endl;
        std::cout << "    Armor: " << _class->getArmor() << std::endl;
    }
};

class Tree : public Entity {
    public:
    Tree(const std::string& name) : Entity(name, Faction::NONE) {}
    
    void debugInfo() const override {
        std::cout << "Tree:" << std::endl;
        std::cout << "    EntityID: " << _id << std::endl;
        std::cout << "    Name: " << _name << std::endl;
    }
};