#include <iostream>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/*
    MIEJSCE NA KOD
*/
template<typename T >
class B{
    private:
    T _t; //przechowyje wartosc typu t
    public:
    using value_type = T;
    B(T t): _t(t){} //zwykly konstructor
    ~B() = default; // destruktor
    //B( T *n ): _t(*n){}
    
    explicit B(const B& other)  : _t(other._t){}// nie mozna kopiowac niejawnie
    B& operator=(const B& other) {
        if(&other!=this){ // b=b - nie dzila ochrona przed samoprzepisaniem 
            _t=other._t;
        }
        return *this;
    }
    
    T get() const{ // mietoda get zwraca copie przechowywanoj wartosci
        return _t;
    }
    friend std::ofstream& operator<<(std::ofstream& os, const B& t){
         os<< t._t;
        return os;
    }
    B& operator()(B &t){
        _t=t._t;
        return *this;
    }


};
template<typename T>
class B<T*>{
    private:
    T *_t;
    public:
    using value_type=T; // *int->int
    B(T *t): _t(t){}
    ~B()=default;
    T get() const{
        return *_t;
    }



}
;

int main()
{
    typedef B<int> int_b;
    typedef B<int*> int_p_b;        //jednak typedef

    int_b a(1);
    int_b a_copy(a);
   int_p_b b(new int_p_b::value_type{2});
    // int_p_b e = b; //error  komientaz- nie mozemy kopiowac niejawnie
    // b=b //error
    
    std::cout << "a=" << a.get() << std::endl;
    std::cout << "a_copy=" << a_copy.get()+1 << std::endl;
    std::cout <<" b=" << b.get()+1 << std::endl;
}

// a=1
// a_copy=2
//  b=3