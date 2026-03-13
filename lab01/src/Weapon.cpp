#include "Weapon.h"

Weapon::Weapon(const std::string& n, int dmg): Item(n), damage(dmg) {}

Weapon::Weapon(const Weapon& other): Item(other.name), damage(other.damage) {}

void Weapon::print(std::ostream& os) const {
    os << "Weapon:" << name << " damage: " << damage << " ";
}

Item* Weapon::clone() const {
    return new Weapon(*this);
}
