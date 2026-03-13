#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Item.h"

class Inventory {
private:
    std::vector<Item*> items;

public:
    Inventory() = default;
    ~Inventory();

    Inventory(const Inventory& other);
    Inventory& operator=(const Inventory& other);

    void add(Item* item);

    Item& operator[](size_t i);
    const Item& operator[](size_t i) const;
    friend std::ostream& operator<<(std::ostream& os, const Inventory& inv);
};

#endif

