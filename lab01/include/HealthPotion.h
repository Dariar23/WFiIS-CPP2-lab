#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "Item.h"

class HealthPotion : public Item {
private:
    int heal;

public:
    HealthPotion(const std::string& n, int h);
    HealthPotion(const HealthPotion& other);

    void print(std::ostream& os) const override;
    Item* clone() const override;
    
};

#endif