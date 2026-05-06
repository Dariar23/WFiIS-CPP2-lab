#include <iostream>
#include <vector>

// Program ma wytworzyć poniższy output.
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.

class Base{

    public:
    virtual std::ostream& print(std::ostream& os) const{
        os << __PRETTY_FUNCTION__ << "\n";
        return os;
    }

};
std::ostream& operator<<(std::ostream& os, const Base &b) {
        return b.print(os);
    }
std::ostream& operator<<(std::ostream&os, const std::vector<Base*>& base){
    for(auto b: base){
        b->print(os);
    }
    return os;
}
class Derived1: public Base{
    public:
    std::ostream& print(std::ostream& os) const override{
        os <<__PRETTY_FUNCTION__ << "\n";
        return os;
    }
    
    Derived1()=default;
    // Derived1 d1_make_err = d2; --- запрещяем копирование 
    Derived1( const Derived1& dq) = delete;




};
class Derived2: public Base{
    public:
    std::ostream& print(std::ostream& os) const override{
        os <<__PRETTY_FUNCTION__ << "\n";
        return os;
    }
    
    
    Derived2()=default;
    Derived2(const Base& other){}
    

};
class Derived3: public Base{
    public:
    std::ostream& print(std::ostream& os) const override{
        os <<__PRETTY_FUNCTION__ << "\n";
        return os;
    }
    Derived3()=default;
    Derived3(const Base& other){}

};
int main(){
    Derived1 d1;
    Derived3 d3;
    Derived2 d2 = d3;
    // Derived1 d1_make_err = d2;

    // std::vector<Base> v_make_err = {d1, d2, d3};
    std::vector<Base*> v = {&d1, &d2, &d3};

    std::cout << *v.front()<<std::endl;
    std::cout << v;
}

/*Wynik:
virtual std::ostream& Derived1::print(std::ostream&) const
[
virtual std::ostream& Derived1::print(std::ostream&) const,
virtual std::ostream& Derived2::print(std::ostream&) const,
virtual std::ostream& Derived3::print(std::ostream&) const
]
*/