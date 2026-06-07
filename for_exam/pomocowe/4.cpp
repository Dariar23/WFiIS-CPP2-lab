
#include <iostream>
#include <vector>

// Program ma wytworzyć poniższy output.
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.
// Kod można pisać tylko w wyznaczonych miejscach.
class Base{
    public:
    virtual ~Base()=default;
    virtual std::ostream& print(std::ostream& os) const {
        os << __PRETTY_FUNCTION__ ;
        return os;

    }

};
class Derived1: public Base{
    public:
    Derived1()=default;
    ~Derived1()=default;
    Derived1(const Derived1& x) = delete;
    std::ostream& print(std::ostream& os) const override{
        os << __PRETTY_FUNCTION__;
        return os;
    }


};
class Derived2:public Base{
    public:
    Derived2()=default;
    ~Derived2()=default;
    std::ostream& print(std::ostream& os) const override{
        os << __PRETTY_FUNCTION__;
        return os;
    }
   Derived2(const Derived2& other) {}

};
class Derived3:public Derived2{
    public:
    Derived3()=default;
    ~Derived3()=default;
    Derived3(const Derived3& other) {}
    std::ostream& print(std::ostream& os) const override{
        os << __PRETTY_FUNCTION__;
        return os;
    }

};

template<typename T>
std::ostream& operator<<(std::ostream&os, std::vector<T*> vec){
    os<<"[ ";
    for(auto it=0; it < vec.size(); it++){
        if(it>0){
            os<<", ";
        }
        os<<*vec[it] <<std::endl;
    }
     os<<" ]"<<std::endl;
     return os;
}
std::ostream& operator<<(std::ostream& os,const Base& obj ) {
        obj.print(os);
        return os;
}
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