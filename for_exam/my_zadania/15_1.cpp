#include <iostream>
#include <memory>
#include <vector>
#include <list>


template< typename T, template<typename U, typename Alloc = std::allocator<U>> class Repo = std::vector>// pirzemy ze Repo jest std::vector defaltowo
// Repo musi byc tez szablonem i przejmowac 2 marametra, bo szablony stl maja taki wzor Container<U, Allocator>
class Repository{
    Repo<std::unique_ptr<T>>  _repo; // kontener an unikalne wskazniki
    public:
    Repository() = default;// potrzebien konstruktor domyslny
    
    void add(std::unique_ptr<T> t){ // dodaje nowy element do _repo
        _repo.push_back(std::move(t));
    }
    size_t size() const{ // zwraca liczbe elementow w _repo
        return _repo.size();
    }
   const T& get(std::size_t i) const {
        auto it = _repo.begin();
        std::advance(it, i);
        return **it;
    }
    void removeLast(){ //usuwanie ostatniego elementa
        _repo.pop_back();
    }
};

int main()
{
    Repository<int, std::vector> repo;//szablon musi byc Repository, std::vector - musi byc allocatorem bo std::vector to szablon nie pszymujacy nic

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