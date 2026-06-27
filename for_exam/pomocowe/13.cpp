#include <iostream>
#include <string>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

class A{
    private:
    
    public:
    std::string s;
    A(std::string str): s(str){
        std::cout << "Tworzenie: " << s << '\n';
    }
    ~A()=default;
    A( const A& other): s(other.s){
        std::cout << "Przenoszenie wersja 2" << '\n';
    } // konstructor kopujancy
    A& operator=(const A& other){
        std::cout << "Kopiowanie wersja 1" << '\n';
        if(&other==this){
            return *this;
        }
        s=other.s;
        return *this;
    }
    A(const A&& other) noexcept: s(other.s){ //konstructor przenoszancy
       std::cout << "Przenoszenie werjsa 1" << '\n';
       
    }
    A& operator=( A&& other){ //konstructor przenoszancy
       this->s=other.s;
        other.s = "";
        std::cout << "Przenoszenie wersja 1" << '\n';
        return *this;
       
    }

   


};
 A f(const A& obj){
        return obj;
    }
int main(){
    A a("var_a"),b("var_b");

    std::cout<<"(1) ->"
                << "a.s ="<<a.s<<" b.s = "<<b.s<<std::endl;
    A c = a; // potrzebien konstruktor kopujancy
    std::cout<<"(2) ->"
                << "a.s ="<<a.s<<" b.s = "<<b.s<<std::endl;
    a = b; /// operator kopujancy
    std::cout<<"(3) ->"
                << "a.s ="<<a.s<<" b.s = "<<b.s<<std::endl;
    a = f(A{"var_c"});

    std::cout<<"(4) ->"
                << "a.s ="<<a.s<<" b.s = "<<b.s<<std::endl;
    b = std::move(a);

    std::cout<<"(5) ->"
                << "a.s ="<<a.s<<" b.s = "<<b.s<<std::endl;
    //b - std::move(b);
}

/*output:
Tworzenie: var_a
Tworzenie: var_b
(1) -> a.s = var_a  b.s = var_b
Kopiowanie wersja 2
(2) -> a.s = var_a  b.s = var_b
Kopiowanie wersja 1
(3) -> a.s = var_b  b.s = var_b
Tworzenie: var_c
Przenoszenie wersja 2
Przenoszenie werjsa 1
(4) -> a.s = var_c  b.s = var_b
Przenoszenie wersja 1
(5) -> a.s =   b.s = var_b
*/