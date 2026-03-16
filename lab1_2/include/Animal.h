#pragma once

#include <string>
#include <iostream>
#include "Zoo.h"

class Animal{

    protected:
    std::string m_name;

    public:
    Animal(const std::string name): m_name(name){}
    virtual ~Animal()=default;
    virtual Animal* clone() const=0;
    virtual void print(std::ostream& os) const = 0;
} ;

inline std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    animal.print(os);
    return os;
}