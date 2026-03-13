
#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
private:
    int damage;

public:
    Weapon(const std::string& n, int dmg);
    Weapon(const Weapon& other);

    void print(std::ostream& os) const override;
    Item* clone() const override;
};

#endif
