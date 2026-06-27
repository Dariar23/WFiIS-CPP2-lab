#include <iostream>

// Co wypisze się na ekran?

struct MyStruct {
    static int j;
    const static int i = 5;
    int a;
};

int i = 10;
int MyStruct::j = i + 1;
int j = i + 1;

namespace exam {
    static int i = 1;
}

int main() {
    MyStruct A;

    A.a = j + i;
    int i = 15;

    using namespace exam;

    std::cout << i << '\n'; //15
    std::cout << ::i << '\n';//global 10
    std::cout << MyStruct::j << '\n';//11
    std::cout << j << '\n';//11
    std::cout << A.a << std::endl;//21
}