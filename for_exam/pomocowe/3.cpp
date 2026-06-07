// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.
#include<iostream>
#include<string>
/* 
    MIEJSCE NA KOD 
*/
class is_printable{
    public:
    virtual ~is_printable()=default;
    virtual void print(std::ostream& os) const =0;

};
class A: public is_printable{
    private:
    std::string _s;
    public:
    A(std::string s): _s(s){}
    ~A()=default;
    friend std::ostream& operator<<(std::ostream& os,const A& obj ){
        os<<obj._s;
        return os;
    }
    std::string get() const{
        return _s;
    }
    void print(std::ostream& os) const override{
        os << _s;
    }

};
class B: public is_printable{
    private:
    int _x;
    public:
    B(int x): _x(x){}
    friend std::ostream& operator<<(std::ostream& os,const B& obj ) {
        os<< obj._x;
        return os;
    }
    int get() const{
        return _x;
    }


    void print(std::ostream& os) const override{
        os << _x;
    }


};
// template< typename T>
std::ostream& operator<<(std::ostream& os,const is_printable& obj ){
    obj.print(os);
    return os;
}

int main()
{
  A a ("Tekst"); 
  B b {123};
  std::cout<< "a:\t"<<a<<"; b:\t"<<b<<"\n";
  const is_printable & a_r = a; 
  const is_printable & b_r = b;
   std::cout<< "a_r:\t"<<a_r<<"; b_r:\t"<<b_r<<"\n";
    return 0;
}

/*
a:      Tekst; b:       123
a_r:    Tekst; b_r:     123
*/