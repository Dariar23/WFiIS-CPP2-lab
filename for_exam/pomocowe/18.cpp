#include <iostream>

// Napisz program który obliczy n-ty wyraz silnii w czasie kompilacji/
// Wypisz wynik na ekran.
// Kod można pisać tylko w wyznaczonych miejscach


constexpr unsigned silnia(unsigned x){
    return  x==0? 1: x*silnia(x-1);
}
int main() {
    std::cout << silnia(5) << std::endl;
}