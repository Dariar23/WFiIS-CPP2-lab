#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

class liftToVector{
    private:
    std::vector<int> history;

    public:
    liftToVector(): history(){} //konstruktor
    ~liftToVector()= default;//destructor
    liftToVector(const liftToVector& other): history(other.history){}  //konstruktor kopujancy
    liftToVector& operator=(const liftToVector& other){
        if(this==&other){
            return *this;
        }
       history=other.history;
       return *this;
    } //operator kopujancy
    std::vector<int> operator()(std::vector<int> vec){ //
        for(int i=0; i < vec.size(); i++){
            history.push_back(vec[i]+2);
        }
        return history;
    }

};

int main(){

    auto vadd2 = liftToVector();
    std::vector<int> x = {0,9,4};
    auto v = vadd2(x);

    std::for_each(v.begin(), v.end(), [](const int n) {std::cout<< n << ' ';});

    return 0;
}

// 2 11 6