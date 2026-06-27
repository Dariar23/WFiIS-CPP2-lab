#include <iostream>
#include <vector>
#include <memory>
#include <list>

// TUTAJ WPISZ SWÓJ KOD
template< typename T = double>
class Type_t{
    public:
    T _v;
    Type_t( T v = T()) : _v(v){}



};
template< typename T>
class ptr{
    private:
    T *_p;
    public:
    using value_type = T;
    explicit ptr(T *p): _p(p){}

    T* operator->(){
        return _p;
    }
    T& operator*(){
        return *_p;
    }
    ptr(ptr&&other) noexcept : _p(other._p){
        other._p=nullptr;
    }
   

};
template< typename T>
std::ostream& operator<<(std::ostream& os, const Type_t<T> & obj){
    os<<obj._v<<" ";
    return os;
}
//// czesc 2
auto print_number(){
    return [](int& x){ std::cout<<x<<" ";};
}
auto print_even(){
    return [](int& x){ if(x%2==0) std::cout<<x<<" ";};
}
auto multiply_by(int mul){
    return [mul](int& x){x*=mul;};
}
template<typename T, typename Function>
void transform(T start, T end, Function f){
    for( T it = start; it != end; it++){
        f(*it);
    }
}
/// czesc 3
class Shape{
    protected:
    double _x;
    public:
    Shape(int x) : _x(x){}
    virtual ~Shape() = default;
    virtual double area() const =0;
    virtual void print_shape(std::ostream& os)=0;


} ;
class Circle: public Shape{
    public:
    Circle(double x): Shape(x){}
    double area() const override{
        return 3.14*_x*_x;
    }
    void print_shape(std::ostream& os) override{
        os << area();
    }

};
class Rectangle: public Shape{
    private :
    double _y;
    public:
    Rectangle(double x, double y): Shape(x), _y(y){}
    double area() const override{
        return _y*_x;
    }
    void print_shape(std::ostream& os) override{
        os << area();
    }

};
class Square: public Shape{
    public:
    Square(double x): Shape(x){}
    double area() const override{
        return _x*_x;
    }
    void print_shape(std::ostream& os) override{
        os << area();
    }

};
template< typename T, typename Function>
void for_each_shape(T begin, T end, Function f){
    for(T it=begin; it !=end; it++){
        f(*it);
    }
}
auto print_shape_info(){
    return [](const std::unique_ptr<Shape>& ptr){
        ptr->print_shape(std::cout);
        std::cout<<std::endl;
    };
}
int main() {
    // ===== CZĘŚĆ 1: Szablon Type_t i inteligentny wskaźnik ptr =====
    using Float_t = Type_t<>;
    using Test_t = ptr<std::pair<Float_t, Float_t>>;

    Test_t t1{new Test_t::value_type{}};
    (*t1).first = Test_t::value_type::first_type{2};
    t1->second = Test_t::value_type::second_type{4.5};

    Test_t t2 = std::move(t1);
    std::cout << "t2: " << (*t2).first._v << ", " << t2->second << std::endl;

    // ===== CZĘŚĆ 2: Lambdy i algorytmy =====
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "\nAll: ";
    for_each(numbers.begin(), numbers.end(), print_number());

    std::cout << "\nEven: ";
    for_each(numbers.begin(), numbers.end(), print_even());

    std::cout << "\nAfter multiply by 3: ";
    transform(numbers.begin(), numbers.end(), multiply_by(3));
    for_each(numbers.begin(), numbers.end(), print_number());

    // ===== CZĘŚĆ 3: Polimorfizm z Shape =====
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Square>(4.0));

    std::cout << "\n\n=== Shapes ===" << std::endl;
    for_each_shape(shapes.begin(), shapes.end(), print_shape_info());

    // std::cout << "\n=== After scale by 2 ===" << std::endl;
    // for_each_shape(shapes.begin(), shapes.end(), scale_shape(2.0));
    // for_each_shape(shapes.begin(), shapes.end(), print_shape_info());

    return 0;
}

/* OCZEKIWANY OUTPUT:
t2: 2, 4.5

All: 1 2 3 4 5 6 7 8 9 10 
Even: 2 4 6 8 10 
After multiply by 3: 3 6 9 12 15 18 21 24 27 30 

=== Shapes ===
Circle: area = 78.5398
Rectangle: area = 24
Square: area = 16

=== After scale by 2 ===
Circle: area = 314.159
Rectangle: area = 96
Square: area = 64
*/