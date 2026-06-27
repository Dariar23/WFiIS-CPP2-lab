#include <utility>

constexpr unsigned factorial(int n){
    if (n == 1) return 1;
    return n * factorial(n-1);
}

template <typename T, unsigned N>
struct array{
    private:
    T _t;
    unsigned _n = N;
  
    public:
   // array( T t,const N Fun(n)): _t(t), _n(Fun(n)){}
   array(): _t(T{}), _n(N){}
   array(const T& t) : _t(t), _n(N) {}
    array(  const array& other): _t(other._t), _n(other._n){}//konstruktor kopujancy
    array( array&& other) noexcept: _t(other._t), _n(other._n){} //konstruktor pszenoszancy
    array& operator=(const array&other){ //operator pszenoszoncy
        if(this!=&other){
            _t=other._t;
            _n=other._n;
        }
        return *this;
    }
    array& operator=(array&other) noexcept{ //operator pszenoszoncy
        if(this!=&other){
            _t = std::move(other._t);
            _n=other._n;
            other._n=0;
        }
        return *this;
    }
    static constexpr unsigned size() {
        return N;
    }


    
};

int main() {
    array<int,6> a;
    const array<int,factorial(3)> b;
    array<int, factorial(4)> c;
    auto d = std::move(c);//potrzebien konstruktor kopujancy
    a=b;//operator przenoszancy
    a=std::move(b);//operator kopujancy
    static_assert(a.size()==6);

    static_assert(array<unsigned,factorial(4)>::size()==24);
    static_assert(array<unsigned,factorial(3)>::size() == b.size());
    // static_assert(array<int, factorial(4)>::size()==b.size()); //blad kompilacji
}