#pragma once
#include <iostream>
#include <string>

class Class {
public:
    virtual ~Class() = default;
    virtual std::string getName() const = 0;
    virtual int getStrength() const = 0;
    virtual int getDexterity() const = 0;
    virtual int getArmor() const = 0;
};

class Warrior : virtual public Class {
public:
    std::string getName() const override {
        return "Warrior";
    }
    int getStrength() const override { return 50; }
    int getDexterity() const override { return 20; }
    int getArmor() const override { return 50; }
};

class Mage : virtual public Class {
public:
    std::string getName() const override {
        return "Mage";
    }
    int getStrength() const override { return 10; }
    int getDexterity() const override { return 10; }
    int getArmor() const override { return 5; }
};

class Archer : virtual public Class {
public:
    std::string getName() const override {
        return "Archer";
    }
    int getStrength() const override { return 20; }
    int getDexterity() const override { return 50; }
    int getArmor() const override { return 30; }
};

class Paladin : public Warrior, public Mage {
public:
    std::string getName() const override {
        return "Paladin";
    }
    int getStrength() const override { 
        return Warrior::getStrength() + Mage::getStrength(); 
    }
    int getDexterity() const override { 
        return Warrior::getDexterity() + Mage::getDexterity(); 
    }
    int getArmor() const override { 
        return Warrior::getArmor() + Mage::getArmor(); 
    }
};

class DragonHunter : public Warrior, public Archer {
public:
    std::string getName() const override {
        return "Dragon Hunter";
    }
    int getStrength() const override { 
        return Warrior::getStrength() + Archer::getStrength(); 
    }
    int getDexterity() const override { 
        return Warrior::getDexterity() + Archer::getDexterity(); 
    }
    int getArmor() const override { 
        return Warrior::getArmor() + Archer::getArmor(); 
    }
};