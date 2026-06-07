#include <iostream>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/

class A{
    public:
    int i;
    A(int ii =1): i(ii){}
    ~A()=default;

};
template<typename T>
class ptr{
    private:
    T *_p;
    public:
    explicit ptr(T *p): _p(p){}
    ptr(): _p(nullptr){}
    ~ptr(){
        delete _p;
    }
    T* operator->() const{
        return _p;
    }
    T& operator*() const{
        return *_p;
    }
    ptr(const ptr&) = delete;

    bool operator==( const ptr<T>&obj)const{
        return _p==obj._p;
    }
    bool operator!=(const ptr<T>&obj) const{
        return _p!=obj._p;
    }
};
int main() {
  const ptr<A>  a(new A);
  const ptr<A> b;
  ptr<A> c(new A);

//   ptr<A>  _b_error = new A;      // Odkomentowanie powoduje błąd kompilacji 
//   a = a;               // Odkomentowanie powoduje błąd kompilacji 
//   const ptr<A> _c_error = a;     // Odkomentowanie powoduje błąd kompilacji 

  std::cout << (((*a).i, a->i))        << " " << ++c->i << " ";
  std::cout << (a == ptr<A>() ) << " " << (a != b) << "\n";
}

//1 2 0 1