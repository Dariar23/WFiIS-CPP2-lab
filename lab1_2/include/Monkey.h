#pragma once
#include "Zoo.h"
class Monkey: public Animal{

    protected:
    int m_age;

    public:
    Monkey(const std::string &name, int age);
    ~Monkey() override=default;
    Animal* clone() const override;
    void print(std::ostream& os) const override;

};