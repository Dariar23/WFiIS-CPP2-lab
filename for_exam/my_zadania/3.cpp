#include <iostream>
#include <vector>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/*
    MIEJSCE NA KOD
*/
template<typename T>
class StackAllocator{
    private:
    char _buffer[64];
    size_t _n;
    public:
    StackAllocator(char buffer[64], size_t n): _buffer(bufer), _n(n){}
    void used(){
        return pow(2,_n);
    }


};

int main()
{
    alignas(int) char buffer[64];
    StackAllocator<int> alloc(buffer, sizeof(buffer)); // konstruktor przejmujancy 2 parametry

    std::vector<int, StackAllocator<int>> v(alloc);
    for (int i : {1,2,3,4,5})
        v.push_back(i);

    for (int x : v) std::cout << x << ' ';
    std::cout << "\n";

    std::cout << "used: " << alloc.used() << "\n";

    // std::vector<int, StackAllocator<int>> v2(alloc);
    // for (int i = 0; i < 100; i++) v2.push_back(i); // powinno wyrzucić std::bad_alloc
}

/*
Wynik (przykładowy, zależny od realokacji vectora):
1 2 3 4 5
used: 32
*/