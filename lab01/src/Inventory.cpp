#include "Inventory.h"


Inventory::~Inventory(){
    for(auto ptr : items){
        delete ptr;
    }
}

Inventory::Inventory(const Inventory& all){
    for( auto ptr : all.items){
        items.push_back(ptr->clone());
    }
}
Inventory& Inventory::operator=(const Inventory& other) {
    if(this == &other){
        return *this;
    }
     
    for(auto ptr : items){
        delete ptr;
    }
        
    items.clear();

    for(auto ptr : other.items){
         items.push_back(ptr->clone());
    }
    return *this;
}

void Inventory::add(Item* item) {
    items.push_back(item);
}

Item& Inventory::operator[](size_t i) {
    return *items[i];
}

const Item& Inventory::operator[](size_t i) const {
    return *items[i];
}

std::ostream& operator<<(std::ostream& os,const Inventory& invent){
    for( auto it : invent.items){
        os << *it<< std::endl;
       
    }
    return os;
}




