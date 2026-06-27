#include <iostream>
#include <vector>
#include <memory>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

template<typename T>
class CountingAllocator{

};
class allocations: public virtual CountingAllocator {

};
int main()
{
    {
        std::vector<int, CountingAllocator<int>> v; //CountingAllocator - to szablon
        v.reserve(2);
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);   // wywoła realokację
        v.pop_back();
    }
    std::cout << "allocs: " << CountingAllocator<int>::allocations << "\n";
    std::cout << "deallocs: " << CountingAllocator<int>::deallocations << "\n";
    std::cout << "live: " << CountingAllocator<int>::allocations -
                              CountingAllocator<int>::deallocations << "\n";
}

/*
Wynik:
allocs: 2
deallocs: 2
live: 0
*/