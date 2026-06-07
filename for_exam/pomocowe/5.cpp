#include<utility>
#include<iostream>
#include<algorithm>

// Program ma wytworzyć poniższy output.
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/


template<typename T = double>
class Type_t{
    public:
    T _v;
    Type_t(T t = T()): _v(t){}
    ~Type_t()=default; 

};
template<typename T>
class ptr{
    private:
    T *_p;
    public:
    using value_type = T;
    explicit ptr(T *p): _p(p){}
    ptr():_p(0){}
    ptr(const ptr&) = delete; // nie mozna kopiowac
    ptr& operator=( ptr&) = delete;
    T* operator->() const{
        return _p;
    }
    T& operator*()const {
        return *_p;
    }
    ptr(ptr&& other) noexcept: _p(other._p) {
        other._p = nullptr;
    }
    ptr& operator=(ptr&& other){
        if(this==&other){
            return *this;
        }
        delete _p;
        _p=other._p;
        other._p=nullptr;
        return *this;   
        
    }
        
    
};
template<typename T>
std::ostream& operator<<(std::ostream& os, const Type_t<T>& obj){
    os<<obj._v;
    return os;
}

using Float_t = Type_t<>; // Type_t - to jest szablon
int main(){
    
    using Type_ptr = ptr<std::pair<Float_t, Float_t>>;
    Type_ptr t1 { new Type_ptr::value_type{}};
    // Type_ptr t2 = t1;  nie mozna kopiowac
    // Type_ptr t2; t2 = t1; // nie mozna przenosic
    // Type_ptr t3 = new Type_ptr::value_type(); // nie nozna niejawni tworzyc object  -> explicit
    (*t1).first = Type_ptr::value_type::first_type{1};
    t1->second = Type_ptr::value_type::second_type{2.5};
    std::cout<< t1->first._v<<" "<<t1->second<<std::endl;

    Type_ptr t2 = std::move(t1);
    // t2->first = 13; 
    //t2->second = 13;
    const Type_ptr t3 = std::move(t2);
    t3->first = Type_ptr::value_type::first_type{13};
    t3->second = Type_ptr::value_type::second_type{13}; 

    std::cout<< (*t3).first._v<<" "<<(*t3).second<<std::endl;
    return 0;
}

// 1 2.5
// 13 13