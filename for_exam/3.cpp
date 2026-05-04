#include<iostream>
#include<string>
using namespace std;
class A{
    private:
    string str;
    public:
    ~A()=default;
    A(string s): str(s){}
    friend std::ostream& operator<<(std::ostream& os, const A& a);
    void is_printable(const A& a) const {
        cout<<this;
    }

};
class B{
    private:
    int n;
    public:
    ~B()=default;
    B(int num): n(num){}
    friend std::ostream& operator<<(std::ostream& os, const B& b){
        os << b.n <<"\n";
        return os;
    }
    void is_printable() const {
        cout<<this;
    }
};
std::ostream& operator<<(std::ostream& os, const A& a){
    os << a.str <<"\n";
    return os;
}

template<typename T>
void is_printable(const T& obj){
    cout<<obj;
}

int main()
{
  A a ("Tekst"); 
  B b {123};
  std::cout<< "a:\t"<<a<<"; b:\t"<<b<<"\n";
  //const is_printable & a_r = a; 
  //const is_printable & b_r = b;
    //std::cout<< "a_r:\t"<<a_r<<"; b_r:\t"<<b_r<<"\n";
}

/*
a:      Tekst; b:       123
a_r:    Tekst; b_r:     123
*/