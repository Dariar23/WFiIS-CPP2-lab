#pragma once

#include "EventBus.h"

class Enemy {

private:
    int m_id;
    int m_hp;
    EventBus& m_bus;

public:
    Enemy(int id, int hp, EventBus& bus);

    void takeDamage(int amount);
    //int getId() const;
    //int getHp() const;


};
