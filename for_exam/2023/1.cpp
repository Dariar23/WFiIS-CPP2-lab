#include <iostream>
#include <vector>
#include <algorithm>
void print(int x){
    std::cout<<x <<" ";

}
void print2(int x){
    std::cout<<x <<",";

}
void parz( int a){
    if(a%2==0){
        std::cout<<a<<" ";
    }
}
bool comp(int a, int b){
    return a>b;
}
void sum( int a, int x=5){
    a+=x;
}

int main(){
    std::vector<int> c = {1,2,3,4,5,6,7};

    std::cout << "c: ";
    std::for_each(c.begin(), c.end(), print);
    //z lambda 
    std::cout<<"\n";
    std::for_each(c.begin(), c.end(),[](int x){std::cout <<x<<" ";});


    std::cout << "\nc parzyste: ";
    std::for_each(c.begin(), c.end(), parz);
    std::cout<<"\n";
    std::for_each(c.begin(), c.end(), [](int x){ if (x%2==0) std::cout<<x<< " ";});

    std::cout << "\nc malejaco: ";
    // std::sort(c.begin(), c.end(), comp);
    // std::for_each(c.begin(), c.end(), print);
    std::sort(c.begin(), c.end(), []( int x, int y){ return x > y;});
    std::for_each(c.begin(), c.end(), [](int x){  std::cout<<"["<<x<< "] ";});

    std::cout << "\nc + x: ";
    int x=5;
    // std::for_each(c.begin(), c.end(), sum);
    // std::for_each(c.begin(), c.end(), print2);
    std::for_each(c.begin(), c.end(), [=](int& a) mutable{ a+=x;});
    std::for_each(c.begin(), c.end(), [](int x){std::cout <<x<<", ";});


    auto f = [&](int a){x+=a; return x;};
    
    std::cout << "\nx: " << x << " ";
    std::cout << "f: " << f(6) << " ";
    std::cout << "x: " << x << std::endl;
}
// /*
// c: 1 2 3 4 5 6 7 
// c parzyste: 2 4 6 
// c malejaco: [7] [6] [5] [4] [3] [2] [1] 
// c + x: 12, 11, 10, 9, 8, 7, 6, 
// x: 5 f: 11 x: 11
// */


// [](){}                           // najprostsza lambda
// [=](){return x+1;}              // przechwytuje wszystkie przez kopię
// [&](){x++;}                     // przechwytuje wszystkie przez referencję
// [x, &y](){x=5; y=10;}           // x kopia, y referencja
// [this](){value=5;}              // w klasie – dostęp do pól
// []() mutable {x++;}             // można modyfikować kopię
// [](int a, int b) -> int {...}   // jawny typ zwracany
// [](auto a, auto b){return a+b;} // generyczna (C++14)