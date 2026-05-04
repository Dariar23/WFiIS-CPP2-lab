#include <iostream>

// Program ma wytworzyć poniższy output.
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.

/* 
    MIEJSCE NA KOD 
*/
using namespace std;
class A{
    private:
    int _a;
    int _b;
    public:
    ~A()=default;
    A(int a, int b): _a(a) , _b(b){
         cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
    }
    A( int b): _a(0) , _b(b){
         cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
    }  
    A(): _a(0) , _b(0){
         cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
    }    
    //friend std::ostream& operator<<(std::ostream &os, const A& obj);  
    // Konstruktor przenoszący
    A(A&& other) noexcept: _a(other._a), _b(other._b){
        cout << "A::[...]: _a=" << _a << ",_b=" << _b << "\n";
        cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
        other._a = 0;
        other._b = 0;
    }  
    
};
//  std::ostream& operator<<(std::ostream& os,const A& obj) {
//         os << __PRETTY_FUNCTION__ << "_a"<<obj._a<<"_b"<<obj._b<<"\n";
//         return os;
//     }

int main()
{
    cout << "a->"; A a;
    cout << "b->"; A b(1);
    cout << "c->"; A c(1,2);

    cout << "d->"; A d = std::move(c);

    // A e = c;
    // A f = 1;
}

/*
a-> A::A(int,int): _a=0,_b=0
A::A(): _a=0,_b=0
b-> A::A(int,int): _a=1,_b=0
A::A(int): _a=1,_b=0
c-> A::A(int,int): _a=1,_b=2
d-> A::[...]: _a=1,_b=2
*/