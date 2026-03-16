#include "Zoo.h"



Zoo::Zoo(const Zoo& other){
    for( auto* it: other.animals){
        animals.push_back(it->clone());
    }
}

//деструктор
Zoo::~Zoo(){
    for( auto *it : animals){
        delete it;
    }
}
// operator przypisania
Zoo& Zoo::operator=(const Zoo& other){
    if(this==&other){
        return *this;
    }
    for( auto *it: animals){
        delete it;
    }  
    animals.clear();
    for( auto *it: other.animals){
        animals.push_back(it->clone());
    }
    return *this;
}
void Zoo::add(Animal* animal){
    animals.push_back(animal);
}

Animal& Zoo::operator[](size_t i){
    return *animals[i];
}
Animal& Zoo::operator[](size_t i) const{
    return *animals[i];
}
std::ostream& operator<<(std::ostream& os, const Zoo& zoo) {
    for (auto* animal : zoo.animals) {
        os << *animal << "\n";
    }
    return os;
}