// Program ma wytworzyć poniższy output.
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.

/* 
    MIEJSCE NA KOD 
*/
#include<iostream>


template<typename T>
class IntArray{
    
    public:
    T arr;
    IntArray(T a): arr(a){}
    using value_type = T;

};
//ArrayPtr - madry wskaznik
template<typename T>
class ArrayPtr{
    private:
    T *_p;
    size_t size;
    public:
    ArrayPtr(T *p, size_t n): _p(p), size(n) {}
    ~ArrayPtr(){
        delete[] _p;
        delete size;
    }
    ArrayPtr(const ArrayPtr&) = delete;// nie mozma kopiowac
    ArrayPtr& operator=(const ArrayPtr&) = delete;

    // mozna przenosic
    //operator prenoszancy
    ArrayPtr& operator=( ArrayPtr&& other) noexcept{
        if(&other==this){
            return *this;
        }
        delete[] _p;
        delete size;
        _p = other._p;
        size=other.size;
        other._p = nullptr;
        other.size=0;

        return *this;
    }
    //constructor pszenosz
    ArrayPtr(ArrayPtr&& other) noexcept: _p( other._p) , size(other.size) {
        other._p = nullptr;
        size=0;
    }
    T& operator[](size_t i){
        return _p[i];
    }
    const T& operator[](size_t i) const{
        return _p[i];
    }

};
template<typename T>
std::ostream& operator<<(std::ostream& os, const T& obj){
    os<< obj._p[i] ;
    return os;
}
int main() {
    using IntArray = ArrayPtr<int>;//ArrayPtr - madry wskaznik
    IntArray a1 { new IntArray::value_type[3]{1, 2, 3} , 3};
    
    // IntArray a2 = a1;  // zabronione kopiowanie
    // IntArray a2; a2 = a1; // zabronione przypisanie kopiujące
    // IntArray a3 = new int[5]; // zabronione niejawne rzutowanie
    
    std::cout << a1[0] << " " << a1[1] << " " << a1[2] << std::endl;
    
    IntArray a2 = std::move(a1);
    // a2 = a2; // powinno być bezpieczne (self-assignment)
    
    a2[0] = 10;
    a2[1] = 20;
    a2[2] = 30;
    
    const IntArray a3 = std::move(a2);
    // a3[0] = 100; // zabronione (const obiekt)
    
    std::cout << a3[0] << " " << a3[1] << " " << a3[2] << std::endl;
    
    return 0;
}

// Oczekiwany output:
// 1 2 3
// 10 20 30