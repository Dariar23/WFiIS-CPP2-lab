#include "Player.h"
#include <algorithm>

Player::Player(int id, int hp, EventBus& bus)
    : m_id(id), m_hp(hp), m_bus(bus) {}

void Player::heal(int amount) {
    m_hp += amount;

    Event e;
    e.type = EventType::PlayerHealed;
    e.data.playerHealed = { m_id, amount, m_hp };
    m_bus.emit(e);
}

void Player::pickItem(const std::string& itemName) {
    Event e;
    e.type = EventType::ItemPicked;
    new (&e.data.itemPicked) ItemPickedData(m_id, itemName);

    m_bus.emit(e);
}

// int Player::getId() const {
//     return m_id;
// }

// int Player::getHp() const {
//     return m_hp;
// }
