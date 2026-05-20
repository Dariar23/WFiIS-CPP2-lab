#include<utility>
#include<iostream>
#include<algorithm>

// Program ma wytworzyć poniższy output.
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.

/* 
    MIEJSCE NA KOD 
*/



template< typename T = double>
class Type_t{
    
    public:
    T _v;
    Type_t(T v=T() ): _v(v){}
    //Type_t(const T&) = delete;

};
using Float_t = Type_t<>; // 
template<typename T>
std::ostream& operator<<(std::ostream& os, const Type_t<T>& obj){
    os << obj._v;
    return os;
}
template<typename T>
class ptr{
    private:
    T* _p;
    public:
    using value_type = T;
    explicit ptr(T* pp): _p(pp){}
    ~ptr(){
        delete _p;
    }
    T* operator->() const {
        return _p;
    }
    T& operator*() const{
        return *_p;
    }
    ptr(const ptr&) = delete;
    ptr& operator=(const ptr& )= delete;

    ptr( ptr&& other): _p(other._p){
        other._p=nullptr;
    }
    //operartor przenoszanczy =
    ptr& operator=(ptr&& other) noexcept{
        if(this==&other){
            return *this;
        }
        delete _p;
        _p=other._p;
        other._p= nullptr;

        return *this;
    }    


};

int main(){
    using Type_ptr = ptr<std::pair<Float_t, Float_t>>;
    Type_ptr t1 { new Type_ptr::value_type{}};
    // Type_ptr t2 = t1;  запрещено присваивание 
    // Type_ptr t2; t2 = t1; заприщено копирование 
    // Type_ptr t3 = new Type_ptr::value_type(); запрещено пользоваться шаблономм для 3
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