#include <iostream>
#include <memory>
#include <vector>
#include <list>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/*
    MIEJSCE NA KOD
*/

int main()
{
    Repository<int, std::vector> repo;

    repo.add(std::make_unique<int>(10));
    repo.add(std::make_unique<int>(20));
    repo.add(std::make_unique<int>(30));

    std::cout << "size: " << repo.size() << "\n";
    std::cout << "first: " << repo.get(0) << "\n";

    repo.removeLast();
    std::cout << "size after remove: " << repo.size() << "\n";

    Repository<std::string, std::list> repo2;
    repo2.add(std::make_unique<std::string>("hello"));
    repo2.add(std::make_unique<std::string>("world"));

    std::cout << "repo2 size: " << repo2.size() << "\n";
    std::cout << "repo2 first: " << repo2.get(0) << "\n";
}

/*
Wynik:
size: 3
first: 10
size after remove: 2
repo2 size: 2
repo2 first: hello
*/