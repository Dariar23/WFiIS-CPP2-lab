#pragma once
#include "Zoo.h"
class Tiger: public Animal{

    protected:
    int m_count;

    public:
    Tiger(const std::string &name, int count);
    ~Tiger() override=default;
    Animal* clone() const override;
    void print(std::ostream& os) const override;

};