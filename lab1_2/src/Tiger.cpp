#include "Tiger.h"

Tiger::Tiger(const std::string &name, int count): Animal(name), m_count(count){}

Animal* Tiger::clone() const {
    return new Tiger(*this);
}
void Tiger::print(std::ostream& os) const{
    os << m_name << " "<< m_count;
}



