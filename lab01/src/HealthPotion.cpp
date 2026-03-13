#include "HealthPotion.h"

//constr
HealthPotion::HealthPotion(const std::string& n, int h): Item(n), heal(h) {}

HealthPotion::HealthPotion(const HealthPotion& other): Item(other.name), heal(other.heal) {}

void HealthPotion::print(std::ostream& os) const {
    os << "HealthPotion: " << name << " heal: " << heal << " ";
}

Item* HealthPotion::clone() const {
    return new HealthPotion(*this);
}
