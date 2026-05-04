#include <iostream>
class Vector{
    private:
    int _x;
    int _y;
    public:
    ~Vector()=default;
    Vector(): _x(0), _y(0){}
    Vector(int x, int y): _x(x), _y(y){}
    // Конструктор копирования
    Vector(const Vector &other): _x(other._x), _y(other._y){}
    //Конструктор перемещения
    Vector(Vector&& other): _x(other._x), _y(other._y){
        other._x=0;
        other._y=0;
    }
    //Оператор копирования
    Vector& operator=(const Vector& other){
        if(this!=&other){
            _x=other._x;
            _y=other._y;
        }
        return *this;
    } 
    //Оператор перемещения
    Vector& operator=(Vector&& other) noexcept{
        if(this != &other){
            _x=other._x;
            _y=other._y;
            other._x =0;
            other._y=0;
        }
        return *this;
    }
    void print(){
        std::cout<<"x= "<<_x <<"y= "<<_y<<"\n";
    }


};

using namespace std;
int main() {
    cout << "1. Default constructor\n";
    Vector v1;
    v1.print();
    
    cout << "\n2. Parameterized constructor\n";
    Vector v2(3, 4);
    v2.print();
    
    cout << "\n3. Copy constructor\n";
    Vector v3 = v2;
    v3.print();
    
    cout << "\n 4. Move constructor\n";
    Vector v4 = std::move(v2);
    v4.print();
    cout << "v2 после move: ";
    v2.print();
    
    cout << "\n5. Copy assignment\n";
    Vector v5;
    v5 = v3;
    v5.print();
    cout << "\n6. Move assignment\n";
    Vector v6;
    v6 = std::move(v3);
    v6.print();
    cout << "v3 после move: ";
    v3.print();
    
}

