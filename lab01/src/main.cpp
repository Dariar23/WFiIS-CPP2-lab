/*
Najważniejsze informacje:
- nie korzystamy z internetu, notatek, kodu sąsiada, etc.
- nie można w żaden sposób modyfikować maina (chyba, że zawiera tylko komentarz z prośbą o jego wypełnienie :))
- CMake musi mieć flagi generujące warningi, tzn. minimum -Wall -Wextra -Wpedantic
- przypominam o istnieniu valgrinda
- będę się czepiać const correctness

- na upela wrzucamy archiwum z plikami źródłowymi oraz CMakeLists.txt, bez katalogu build
    * w prostych programach proszę się trzymać podziału na include i src, 
    * jeśli pojawi nam się większy projekt, podział na podkatalogi z użyciem include_directory w CMake jest jak najbardziej ok
    * tar -czvf nazwa.tar.gz zad/ :)
- proszę czytać wstępy i feedback
*/

#include <iostream>
#include "Weapon.h"
#include "HealthPotion.h"
#include "Inventory.h"

int main() {

    Inventory inventory;

    inventory.add(new Weapon("Sword", 25));
    inventory.add(new HealthPotion("Medium Health Potion", 50));

    std::cout << "=== POCZATKOWA ZAWARTOSC INVENTORY ===\n";
    std::cout << inventory << std::endl;

    std::cout << "=== DODANIE NOWEGO ITEMU ===\n";
    inventory.add(new Weapon("Axe", 40));

    std::cout << "=== AKTUALNA ZAWARTOSC ===\n";
    std::cout << inventory << std::endl;

    std::cout << "=== POJEDYNCZY ELEMENT ===\n";
    std::cout << inventory[0] << std::endl;

    const Inventory& cref = inventory;

    std::cout << "=== POJEDYNCZY ELEMENT (CONST) ===\n";
    std::cout << cref[1] << std::endl;

    Inventory copy = inventory;

    std::cout << "=== KOPIA INVENTORY ===\n";
    std::cout << copy << std::endl;

    std::cout << "=== MODYFIKACJA ORYGINALU (dodanie itemu) ===\n";
    inventory.add(new HealthPotion("Small Health Potion", 20));

    std::cout << "=== ORYGINAL PO MODYFIKACJI ===\n";
    std::cout << inventory << std::endl;

    std::cout << "=== KOPIA PO MODYFIKACJI ORYGINALU (nie powinna sie zmienic) ===\n";
    std::cout << copy << std::endl;

    return 0;
}

/** 
Na rozgrzewkę, żebyście wiedzieli jak sobie radzić gdy potrzebujemy polimorfizmu tam, gdzie nie da się go bezpośrednio użyć. :)

Założenia:

1. Weapon i HealthPotion mają (wspólne) pole nazwy, a dodatkowo:
    * Weapon ma pole zadawanych obrażeń
    * HealthPotion ma pole mówiące ile HP przywraca 

    Proszę zaimplementować je jako klasy z odpowiednim interfejsem.

2. Ekwipunek przechowuje całą zawartość w jednym kontenerze jako wskaźnik na klasę bazową.
    * Przejmuje własność nad dodanymi obiektami i ich pamięcią
    * uwaga na operator[] - ma bardzo konkretną sygnaturę i zwracany typ :)

Zwracam uwagę, że mamy mały problem, bo chcemy zaimplementować kopiowanie i wypisanie, ale mamy dostęp tylko do wskaźnika na klasę bazową.
Z drugiej strony, ani konstruktor/operator kopiujący, ani operator wypisania nie mogą być wirtualne, bo mają różne sygnatury w klasie bazowej i pochodnych.

Trzeba sobie poradzić odpowiednimi metodami pomocniczymi.
*/