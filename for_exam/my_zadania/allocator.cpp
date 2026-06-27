#include <iostream>
#include <vector>
#include <list>
#include <memory>

// ==================== WRAPPER ====================
template<typename T>
class Wrapper {
private:
    std::unique_ptr<T> _ptr;  // ✅ Używamy unique_ptr zamiast surowego wskaźnika

public:
    // Konstruktor z unique_ptr
    explicit Wrapper(std::unique_ptr<T> ptr) : _ptr(std::move(ptr)) {}

    // Konstruktor z surowym wskaźnikiem
    explicit Wrapper(T* ptr) : _ptr(ptr) {}

    // Konstruktor z wartością (tworzy nowy obiekt)
    explicit Wrapper(T value) : _ptr(std::make_unique<T>(value)) {}

    // Konstruktor kopiujący = delete
    Wrapper(const Wrapper& other) = delete;

    // Konstruktor przenoszący
    Wrapper(Wrapper&& other) noexcept : _ptr(std::move(other._ptr)) {}

    // Operator przypisania przenoszącego
    Wrapper& operator=(Wrapper&& other) noexcept {
        if (this != &other) {
            _ptr = std::move(other._ptr);
        }
        return *this;
    }

    // Operator wyłuskania (dla *w2)
    T& operator*() const {
        return *_ptr;
    }

    // Przyjaciel dla operator<<
    friend std::ostream& operator<<(std::ostream& os, const Wrapper& obj) {
        os << *obj._ptr;
        return os;
    }
};

// ==================== ADAPTER ====================
template<typename T, template<typename U, typename Alloc = std::allocator<U>> class Container = std::vector>
class Adapter {
private:
    Container<Wrapper<T>> _lista;

public:
    Adapter() = default;

    Adapter(Adapter&& other) noexcept : _lista(std::move(other._lista)) {}

    Adapter& operator=(Adapter&& other) noexcept {
        if (this != &other) {
            _lista = std::move(other._lista);
        }
        return *this;
    }

    void add(Wrapper<T>&& t) {
        _lista.push_back(std::move(t));
    }

    void print_elements() const {
        for (const auto& item : _lista) {
            std::cout << item << " ";  // item to Wrapper<T>, używa operator<<
        }
        std::cout << "\n";
    }
};

// ==================== MAIN ====================
int main() {
    // Wrapper przechowuje unikalny wskaźnik na typ int
    Wrapper<int> w1(new int{10});
    Wrapper<int> w2(20);

    // Wrapper<int> error_1 = w1;       // BŁĄD KOMPILACJI (brak kopiowania)
    // Wrapper<int> error_2 = 30;       // BŁĄD KOMPILACJI (explicit)

    Wrapper<int> w3 = std::move(w1);    // OK (semantyka ruchu)

    std::cout << "w2: " << *w2 << ", w3: " << *w3 << "\n";

    // Adapter przyjmuje TYP danych oraz SZABLON kontenera
    Adapter<int, std::vector> vec_adapter;
    vec_adapter.add(std::move(w2));
    vec_adapter.add(std::move(w3));

    Adapter<int, std::list> list_adapter;
    list_adapter = std::move(vec_adapter);  // Operator przenoszący

    std::cout << "Elementy w liscie: ";
    list_adapter.print_elements();
}