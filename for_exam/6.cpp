#include <iostream>
class Math {
public:
    double calculate(double a, int b) { return a * b; }
};
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int multiply(int a, int b) { return a * b; }
};


int main() {
    Math obj;
    
    // 1. Deklaracja wskaźnika methodPtr:
   double (Math::*methodPtr)(double, int);
    
    // 2. Inicjalizacja (przypisanie adresu funkcji):
    methodPtr=&Math::calculate;
    
    // 3. Wywołanie przez wskaźnik z argumentami 3.14 i 2:
    double res=(obj.*methodPtr)(3.14,2);

    Calculator calc;
    
    // Zadeklaruj wskaźnik o nazwie 'op' do funkcji składowej klasy Calculator,
    int (Calculator::*op)(int, int);
    // która zwraca int i przyjmuje dwa parametry int.
    // Następnie przypisz do niego funkcję multiply i wywołaj z argumentami 5 i 3.
    op = &Calculator::multiply;
    int (Calculator::*fun)(int, int) = &Calculator::add;
    int res2=(calc.*fun)(2,3);
    int res=(calc.*op)(5,3);

  
    
}