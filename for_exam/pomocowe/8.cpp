#include <iostream>
// KlasaBazowa& ref = obiektKlasyPochodnej;   // ✅ działa
// KlasaPochodna& ref = obiektKlasyBazowej;   // ❌ NIE działa (bez rzutowania)
// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

class Obj{
    public:
    //virtual ~Obj() = default;
    virtual void Draw() const =0 ;

};
template<typename T>
class Box: public Obj{
    private:
    T _t;
    public:
    explicit Box(const T t): _t(t){}

    template<typename U>
    Box(const U& u): _t(u){}

    void Draw()const override{
        std::cout <<__PRETTY_FUNCTION__<<_t<<std::endl;
        // std::cout << _t << std::endl;  
    }
    operator T() const {
        return _t;
    }
    friend std::ostream& operator<<(const std::ostream&os, const T& t){
        os << t._t;
        //return os;
    }
    // Box(const T&other): _t(other._t){}
    // Box& operator=(const T& other){
    //     if(&other==this){
    //         return *this;
    //     }
    //     _t=other._t;
    //     return *this;
    // }


};


int main()
{
    Box<int> b_i {3};        
    Obj& r_1 = b_i; // b_i jest objektem Box<int>, r_i- jest referencja
    r_1.Draw(); 
    int i = b_i; // musi byc constructor copujacy
    Box<double> b_d {3.4} ;
    Obj& r_2 = b_d;
    r_2.Draw(); 
    double d = b_d; //potrzebien operator konwersci to typu T
    Box<Box<int>> bb_i {3} ;
    const Obj& r_3 = bb_i;
    r_3.Draw(); 
    Box<int> br_i = bb_i;
    Box<Box<double>> bb_d {3.4} ; 
    const Obj& r_4 = bb_d;
    r_4.Draw();
    Box<double> b_a = bb_d;

    // Box<int> _ = 3; //Odkomentowanie powoduje b��d kompilacji //nie mozna zmieniac niejawnite? to oznacza ze potrzebien explicit

}
/*
void Box<T>::Draw() const [with T = int] --> 3
void Box<T>::Draw() const [with T = double] --> 3.4
void Box<Box<K> >::Draw() const [with T = int] --> 3
void Box<Box<K> >::Draw() const [with T = double] --> 3.4
*/