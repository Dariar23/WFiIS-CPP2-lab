#include <iostream>
#include <vector>
#include <memory>

// TUTAJ WPISZ SWÓJ KOD
struct Shape{
    protected:
    double _x;
    public:
    Shape(double x): _x(x){} 
    virtual ~Shape() = default;
    virtual double area() const =0;
    virtual void print_shape(std::ostream & os) const =0;

};
struct Circle: Shape{ 
    Circle(double x): Shape(x){}
    double area()const override {
        return 3.14*_x*_x;
    }
    void print_shape(std::ostream & os) const override{
        os << "Circle: area = " << area();
    }

};
struct Rectangle: Shape{
    private:
    int _y;
    public:
    Rectangle(double x, double y): Shape(x), _y(y){}
    double area( ) const override {
        return _x*_y;
    }
    void print_shape(std::ostream & os) const override{
        os<< "Rectangle: area = " << area();
    }

};
struct Square: Shape{
    Square(double x): Shape(x){}
    double area( ) const override {
        return _x*_x;
    }
    void print_shape(std::ostream & os) const override{
        os << "Square: area = "<< area();
    }

};
template<typename T, typename Function>
void my_for_each(T begin, T end, Function f){
    for( T it = begin ; it!=end; ++it){
        f(*it);
    }
}
auto print_shape() {
    return [](const std::unique_ptr<Shape>& ptr) {
        ptr->print_shape(std::cout);
        std::cout << std::endl;
    };
}
std::ostream& operator<<(std::ostream& os, const Shape& obj){
    obj.print_shape(os);
    return os;
}
template<typename T, typename Function >
void print_if(std::ostream& stream, T start, T end, Function f){
    for( auto it = start; it !=end; it++){
        f(*it);
    }
}
auto always_true(){
    return [](int &x){ std::cout<< x<< " ";};
}
auto is_even=[](int x){if(x%2==0) std::cout<< x << " ";};
auto multiply_by(int mul){
    return [mul](int &x){ x*=mul;};
}
template< typename T , typename Function>
void transform(T begin, T end, Function f){
    for( T it = begin; it != end; it++){
        f(*it);
    }
}
template< typename T , typename Function>
void transform_shapes(T begin, T end, Function f){
    for( T it = begin; it != end; it++){
        f(*it);
    }
}
auto multiply_by(double scale){
    return [scale](double &x){ x*=scale;};
}
int main() {
    // ===== CZĘŚĆ 1: Dziedziczenie i polimorfizm =====
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Circle>(3.0));
    shapes.push_back(std::make_unique<Square>(4.0));
    
    std::cout << "=== Shapes ===" << std::endl;
    my_for_each(shapes.begin(), shapes.end(), print_shape());
    
    // ===== CZĘŚĆ 2: Filtrowanie i transformacja =====
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "\n=== Numbers ===" << std::endl;
    print_if(std::cout << "All: ", numbers.begin(), numbers.end(), always_true());
    print_if(std::cout << "Even: ", numbers.begin(), numbers.end(), is_even);
    print_if(std::cout << "Greater than 5: ", numbers.begin(), numbers.end(), 
             [](int x) { if (x > 5) std::cout << x<< " "; });
    
    // ===== CZĘŚĆ 3: Modyfikacja przez funkcję zwracającą lambdę =====
    transform(numbers.begin(), numbers.end(), multiply_by(3));
    std::cout << "\nAfter multiply by 3: ";
    print_if(std::cout << "", numbers.begin(), numbers.end(), always_true());
    
    // ===== CZĘŚĆ 4: Polimorfizm z funkcją modyfikującą =====
    // transform_shapes(shapes.begin(), shapes.end(), scale(2.0));
    // std::cout << "\n=== After scale by 2 ===" << std::endl;
    // for_each(shapes.begin(), shapes.end(), print_shape());
    
    return 0;
}

/* OCZEKIWANY OUTPUT:
=== Shapes ===
Circle: area = 78.5398
Rectangle: area = 24
Circle: area = 28.2743
Square: area = 16

=== Numbers ===
All: 1 2 3 4 5 6 7 8 9 10 
Even: 2 4 6 8 10 
Greater than 5: 6 7 8 9 10 

After multiply by 3: 3 6 9 12 15 18 21 24 27 30 

=== After scale by 2 ===
Circle: area = 314.159
Rectangle: area = 96
Circle: area = 113.097
Square: area = 64
*/