#include <iostream>
#include <list>
#include <functional>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

class f3 {
    public:
    f3(int add_value) {
        _add_value = add_value;
    }
    int operator()(int value) {
        return value + _add_value;
    }
    private:
    int _add_value;
};

template<typename T, typename Function>
void print_to_if(std::ostream &os, T begin, T end, Function fun){
    for(auto it = begin; it != end; it++){
        fun(*it);
    }
    std::cout<<std::endl;

}
template<typename T>
void change(T begin, T end, f3 fun){
    for(auto it=begin; it!=end; it++ ){
       *it = fun(*it);
    }
    //std::cout<<std::endl;
}

auto f1 =[](int x){ std::cout<<x<< " ";};
auto f2=[](int x){ if( x%2==0) std::cout<<x<<" ";};
// template<int delta>
// auto f3 = [](int x){x+=delta;};



int main(){
    const auto cl = {1,2,3,4,5,6,7};

    print_to_if(std::cout<<"All: ", begin(cl), end(cl), f1);
    print_to_if(std::cout<<"All: ", begin(cl), end(cl), f2);

    int add_value{-1};
    std::list<int> cl2 = {7,6,5,4,3,2,1};
    change(begin(cl2), end(cl2), f3{add_value}); //listy inicyalizacji
    print_to_if(std::cout << "All  ", begin(cl2), end(cl2), f1);
}
/*
All: 1 2 3 4 5 6 7 
All: 2 4 6 
All  6 5 4 3 2 1 0 
*/