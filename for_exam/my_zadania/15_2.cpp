#include <iostream>
#include <memory>
#include <string>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.
// Po odkomentowaniu zakomentowanej linii w main program ma się NIE kompilować.

//Pack- to jest szablon
template<typename T>
class Pack{
    private:
    T _t;
    std::string _s;
    public:
    Pack(): Pack(0,""){//konstruktor domyslny
        std::cout<< __PRETTY_FUNCTION__<<std::endl;
    } 
    Pack(T t): Pack(t,""){
        std::cout<< __PRETTY_FUNCTION__<<std::endl;
    }
    Pack(T t, std::string s): _t(t), _s(s){
        std::cout<< __PRETTY_FUNCTION__<<std::endl;
    }
    Pack(const Pack& other)=delete;
    Pack( Pack&& other) noexcept: _t(std::move(other._t)), _s(std::move(other._s)){ }
    T& value() const{ //zwraca wartosc
        return _t;
    }
    std::string& label()const { //zwraca stringa
        return _s;
    }



};
template<typename T>
class Pack<Pack<T>>{
    private:
    Pack<T> _t;
    public:
    Pack<Pack<T>>(Pack<T> t) :_t(t){}
    Pack<T>& value(){
        //_t.value();
        return _t;
    }

};
//potrzebien zeby dzilal cout
using namespace std;
int main()
{
    cout << "p1->"; Pack<int> p1; // potrzebien konstruktor defoltowy
    cout << "p2->"; Pack<int> p2(5); // potrzebien konstruktor pszyjmujancy 1 parametr
    cout << "p3->"; Pack<int> p3(5, "label-A");// potrzebien konstruktor pszyjmujancy 2 parametra

    std::cout << "p3 value: " << p3.value() << ", label: " << p3.label() << "\n";

    cout << "pp->"; Pack<Pack<int>> pp(p3); //szablon w szablonie

    std::cout << "pp.value().value(): " << pp.value().value() << "\n"; // value musi zwracac referencje sam na siebie

    // Pack<int> bad = p3;   // odkomentowanie powoduje błąd kompilacji (copy zabronione) -> konstruktor kopujancy =delete
    Pack<int> moved = std::move(p3);
    std::cout << "moved value: " << moved.value() << "\n";
}

/*
Wynik:
p1-> Pack::Pack(int,string): value=0, label=
Pack::Pack(): value=0, label=
p2-> Pack::Pack(int,string): value=5, label=
Pack::Pack(int): value=5, label=
p3-> Pack::Pack(int,string): value=5, label=label-A
p3 value: 5, label: label-A
pp-> Pack::Pack(Pack<int>): value=5, label=label-A (copied into wrapper)
pp.value().value(): 5
moved value: 5
*/