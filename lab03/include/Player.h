#pragma once
#include <string>
#include "EventBus.h"

class Player {
private:
    int m_id;
    int m_hp;
    EventBus& m_bus;   

public:

    Player(int id, int hp, EventBus& bus);
    void heal(int amount);
    void pickItem(const std::string& itemName);

    // int getId() const;
    // int getHp() const;


};
