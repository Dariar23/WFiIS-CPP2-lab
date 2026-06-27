#include <iostream>

// KOD MOŻNA PISAĆ TYLKO W WYZNACZONYCH MIEJSCACH

/* 
Printable - to klassa bazowa
SmartBox - klassa pochodna
*/
class Printable{
    public:
    virtual void print() const = 0;
    virtual ~Printable() = default;

};
template <typename T = double>
class SmartBox: public Printable {
    
    private:
    T *value;
    public:
    SmartBox( const T &val): value(new T(val)){} // zwykly kostructor
    SmartBox( const SmartBox& other) = delete;
    SmartBox& operator=(const SmartBox&) = delete;
    SmartBox(SmartBox&& other) noexcept : value(other.value) {
        other.value = nullptr;
    }
    SmartBox& operator=(SmartBox&& other) noexcept {
    if (this != &other) {
        delete value;
        value = other.value;
        other.value = nullptr;
    }
    return *this;
}
    ~SmartBox() { // destruktor
        delete value;
    }
     SmartBox(std::nullptr_t): value(nullptr){} // konstructor dla nullptr
    //dla test 3

    // template< typename K>
    // SmartBox( const K& u) : value(u){}
    // operator T<K>{
    //     return *value;
    // }

    operator T() const {
        return value? *value : T();
    }
    operator T*() const {
        return value;
    }
    void print() const override{
         std::cout <<__PRETTY_FUNCTION__<<" --> "<<*value<<std::endl;
    }
   T& operator*() const{
        return *value;
    }
    explicit operator bool() const {
    return value != nullptr;
}   
};
template< typename K>
class SmartBox<SmartBox<K>>: public Printable{
    private:
    SmartBox<K> *value;
    public:
    SmartBox( const K& u) : value(new SmartBox<K>(u)){}
    void print() const override{
         std::cout <<__PRETTY_FUNCTION__<<" --> "<<**value<<std::endl;
    }
    SmartBox(const SmartBox&) = delete;
    SmartBox& operator=(const SmartBox&) = delete;
    operator SmartBox<K>() const {
        return value ? std::move(*value) : SmartBox<K>(nullptr);
    }
    operator K() const {
    return value ? **value : K();
    }
    SmartBox(SmartBox&& other) noexcept : value(other.value) {
        other.value = nullptr;
    }
    SmartBox& operator=(SmartBox&& other) noexcept {
    if (this != &other) {
        delete value;
        value = other.value;
        other.value = nullptr;
    }
    return *this;
    }
    ~SmartBox() { // destruktor
        delete value;
    }
    SmartBox(std::nullptr_t): value(nullptr){} 
    explicit operator bool() const {
        return value != nullptr;
    }

};


int main() {
    // Test 1: Podstawowe działanie
    SmartBox<int> s1 = 10;           // niejawna konwersja - to oznacza ze nie urzywamy explicit i potrzebien jest operator konwersji 
    const Printable& p1 = s1;   //konstructor kopujancy
    p1.print();                       // SmartBox<int>::print() --> 10
    
    int* ptr = s1;                    // konwersja do wskaźnika
    *ptr = 20;
    s1.print();                       // SmartBox<int>::print() --> 20
    
    // Test 2: Operator bool
    SmartBox<double> s2(nullptr);     // explicit z nullptr
    if (!s2) std::cout << "empty\n";  // wypisuje "empty"
    
    // Test 3: Zagnieżdżanie
    SmartBox<SmartBox<int>> s3 = 30;   // tworzy SmartBox<int>(30) wewnątrz
    const Printable& p3 = s3;
    p3.print();                        // SmartBox<SmartBox<K>>::print() with K = int --> 30
    
    int value = s3;                    // konwersja SmartBox<SmartBox<int>> -> int
    std::cout << value << "\n";        // wypisuje 30
    
    SmartBox<int> s4 = s3;             // konwersja SmartBox<SmartBox<int>> -> SmartBox<int>
    s4.print();                        // SmartBox<int>::print() --> 30
    
    // Test 4: MOVE (kopiowanie zabronione)
    SmartBox<int> s5 = std::move(s1);  // move konstruktor
    // SmartBox<int> s6 = s1;          // Odkomentowanie powoduje błąd kompilacji!
    
    // Test 5: Operator ->
    *s5 = 100;                         // przez operator*()
    s5.print();                        // SmartBox<int>::print() --> 100
    
    std::cout << "---\n";
}

/*
OCZEKIWANY OUTPUT:
SmartBox<int>::print() --> 10
SmartBox<int>::print() --> 20
empty
SmartBox<SmartBox<K>>::print() with K = int --> 30
30
SmartBox<int>::print() --> 30
SmartBox<int>::print() --> 100
---
*/