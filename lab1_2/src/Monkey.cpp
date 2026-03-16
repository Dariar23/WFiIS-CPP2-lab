#include "Monkey.h"

Monkey::Monkey(const std::string &name, int age): Animal(name), m_age(age){}

Animal* Monkey::clone() const {
    return new Monkey(*this);
}
void Monkey::print(std::ostream& os) const{
    os << m_name << " "<< m_age;
}