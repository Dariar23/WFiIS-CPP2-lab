#pragma once

#include <vector>
#include "Animal.h"
class Zoo{

    private:
    std::vector<Animal*> animals;

    public:
    //конструктор копирования dla wszystkich animals
    Zoo(const Zoo& other);
    Zoo()=default;
    //деструктор
    ~Zoo();
    // operator przypisania
    Zoo& operator=(const Zoo& other);
    void add(Animal* animal);

    Animal& operator[](size_t i);
    Animal& operator[](size_t i) const;

    friend std::ostream& operator<<(std::ostream& os, const Zoo& animal);
};


