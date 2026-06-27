#include <iostream>
#include <utility>

/* Uzupelnij 1 */
template <typename T = double>
class Type_t{
    public:
    T _v;
    Type_t( T v = T()): _v(v){}
};
template <typename T>
class ptr{
    private:
    T *_p;
    public:
    using value_type=T; //будет сообщять какой тип храниться внутри контейнера 
    explicit ptr(T *p): _p(p){} // nie mozna niejawniw tworzyc objectu
    ptr(): _p(nullptr){}
    ~ptr(){
        delete _p;
    }
    ptr(const ptr&)=delete; // nie mozna kopiowac
    ptr& operator=(const ptr&p) = delete; // nie mozna przenosic 

    

    T* operator->() const {
        return _p;
    }
    T& operator*() const {
        return *_p;
    }
    ptr(ptr&& other) noexcept: _p(other._p){
        other._p= nullptr;
    } //  Konstruktor przenoszący
    ptr& operator=( ptr&& other) { // operator przenoszący
        if(this==&other){
            return *this;
        }
        delete _p;
        _p=other._p;
        other._p=nullptr;
        return *this;
    }
    ptr( const ptr&& other): _p(other._p){} 



};
template <typename T>
std::ostream &operator<<(std::ostream& os, const Type_t<T>& obj){
    os << obj._v;
    return os;
}

// Type_t to opakowywacz
using namespace std;
int main()
{
    using Float_t = Type_t<>;
    using Test_t = ptr<std::pair<Float_t, Float_t>>;

    Test_t t1{new Test_t::value_type{}};
    // Test_t t2 = t1;                            // BLAD KOMPILACJI
    // Test_t t3; t3 = t1;                        // BLAD KOMPILACJI
    // Test_t t4 = new Test_t::value_type();    // BLAD KOMPILACJI

    (*t1).first = Test_t::value_type::first_type{1};
    t1->second = Test_t::value_type::second_type{3.141};

    Test_t t2; /// potrzeben konstructor domyslny
    t2 = std::move(t1);
    std::cout << (*t2).first << ", " << t2->second._v << "\n";

    const Test_t t3 = std::move(t2);
    // (*t3).first = 13;       //  BLAD KOMPILACJI
    // t3->second = 13;        //  BLAD KOMPILACJI

    std::cout << (*t3).first._v << ", " << t3->second << "\n";
}
/* output:
1, 3.141
1, 3.141
*/