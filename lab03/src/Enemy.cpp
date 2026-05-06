#include "Enemy.h"
#include <algorithm>

Enemy::Enemy(int id, int hp, EventBus& bus)
    : m_id(id), m_hp(hp), m_bus(bus) {}

void Enemy::takeDamage(int amount) {
    m_hp = std::max(0, m_hp - amount);

    Event e;
    e.type = EventType::EnemyDamaged;
    e.data.enemyDamaged = { m_id, amount, m_hp };
    m_bus.emit(e);
    
    if (m_hp == 0) {
       Event e2;
        e2.type = EventType::EnemyDied;
        e2.data.enemyDied = { m_id };
        m_bus.emit(e2);
    }
}

// int Enemy::getId() const {
//     return m_id;
// }

// int Enemy::getHp() const {
//     return m_hp;
// }
