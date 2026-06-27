#include <iostream>
#include <stdexcept>
#include<initializer_list>
#include<vector>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.
template<typename T = int >
class box{
    private:
    T _t;
    public:
    box(T t): _t(t){} //konstrukto
    ~box() = default;// destructor;
    using value_type = T;
    T get() const { return _t; }
   
   
};
template<typename Box=box<int>>
class array{
    private:
    std::vector<Box> _vec; // pszechowujemy kontenery
    public:
    using value_type = box<int>;
    array(std::initializer_list<Box> vec): _vec(vec){} // konstruktor
    ~array()=default; //destructor
    array(const array&other): _vec(other._vec){}
    size_t size() const{
        return _vec.size();
    }
    Box& operator[](int i) {
        if (i < 0) i = _vec.size() + i;
        return _vec[i];
    }
    const Box& operator[](int i) const {
        if (i < 0) i = _vec.size() + i;
        return _vec[i];
    }
    

};
template<typename T>
std::ostream& operator<<(std::ostream& os, const box<T>& b) {
    os << b.get();
    return os;
}
template<typename T>
void print(const array<T>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    array<box<>> a = {5, 6, 7}; // Inicjalizacja tablicy z wartościami
    const array<box<>> b = a;   // Kopiowanie tablicy - musi byc konstruktor kopujancy

    a[-1] = array<box<>>::value_type{2}; // Ustawienie wartości w ostatnim elemencie
    a[-a.size()] = box<>::value_type{3}; // Ustawienie wartości w pierwszym elemencie

    print(a); // Wydrukowanie tablicy a
    print(b); // Wydrukowanie tablicy b
}

// 3 6 2
// 5 6 7