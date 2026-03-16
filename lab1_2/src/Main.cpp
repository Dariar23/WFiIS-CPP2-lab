#include <iostream>
#include "Zoo.h"
#include "Tiger.h"
#include "Monkey.h"

int main() {
    Zoo zoo;

    zoo.add(new Tiger("Shere Khan", 88));
    zoo.add(new Monkey("Abu", 12));
    zoo.add(new Tiger("Richard Parker", 102));

    std::cout << "Original zoo:\n";
    std::cout << zoo << std::endl;

    // Проверка глубокого копирования
    Zoo copy = zoo;

    std::cout << "Copied zoo:\n";
    std::cout << copy << std::endl;

    // Проверка operator[]
    std::cout << "First animal in original: ";
    std::cout << zoo[0] << std::endl;

    const Zoo& cref = zoo;
    std::cout << "Second animal (const): ";
    std::cout << cref[1] << std::endl;

    return 0;
}
