#include <iostream>

template <typename T1, typename T2>
class my_pair {
    public:
    std::pair<T1,T2> _pair;
    using first_type = T1;
    using second_type = T2;

    my_pair(T1 t1, T2 t2): _pair(std::make_pair(t1,t2)){}
    my_pair(T1 t1):my_pair(t1,0){}
     my_pair(T1 t2):my_pair(0,t2){}
};

template <typename T>
class ptr {
    T* ptr_;
public:
    using value_type = T;

    explicit ptr(T* p) : ptr_(p) {}
    ~ptr() { delete ptr_; }

    ptr(const ptr&) = delete;
    ptr& operator=(const ptr&) = delete;

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
};

int main()
{
    using Float_t = double;
    using Test_t = ptr<my_pair<Float_t, Float_t>>;

    Test_t t1{new Test_t::value_type{}};
    // Test_t t2 = t1;                            // BLAD KOMPILACJI
    // Test_t t3; t3 = t1;                        // BLAD KOMPILACJI
    // Test_t t4 = new Test_t::value_type();      // BLAD KOMPILACJI

    std::cout << (*t1).first << ", " << t1->second << "\n";

    (*t1).first = Test_t::value_type::first_type{1};
    t1->second = Test_t::value_type::second_type{3.141};

    std::cout << (*t1).first << ", " << t1->second << "\n";

}