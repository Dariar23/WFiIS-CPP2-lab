#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
protected:
    std::string name;

public:
    Item(const std::string& n) : name(n) {}
    virtual ~Item() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual Item* clone()const =0;
    
};

inline std::ostream& operator<<(std::ostream& os, const Item& item) {
   item.print(os);
   return os;
}

#endif