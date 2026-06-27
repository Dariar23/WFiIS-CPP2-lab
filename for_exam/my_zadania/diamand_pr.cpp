#include <iostream>
#include<string>
// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

// jezeli pole nie w abstract class to musi byc public

class Base{
    private:
    std::string name;
    public:
    virtual ~Base() = default;
    virtual void show() const {
        std::cout<<"Base::show() [common]"<<std::endl;
    }
};
class A :public virtual Base{
    public:
    std::string name;
    A()=default;
    A(const A&other): name(other.name){} 
};
class B :public virtual Base{
    
    public:
    B()=default;
    std::string name;
    B(const B&other): name(other.name){} 
};
class D: public A, public B{
    public:
    std::string name;
    D()=default;
    void show() const override {
            std::cout << "A: " << A::name << "; B: " << B::name <<std::endl;
    }
};
 
int main()
{
    D d;
    d.A::name = "base-A"; //operator pszenoszancy
    d.B::name = "base-B"; // operator pszenoszoncy

    d.show();

    Base& r = d; // base klasa bazowa, D - klassa pochodna 
    r.show();//motoda wypisania

    std::cout << (&d.A::name == &d.B::name) << "\n";
}

/*
Wynik:
A: base-A; B: base-B; C: child
Base::show() [common]
1
*/