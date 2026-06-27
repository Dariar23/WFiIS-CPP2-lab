#include<iostream>
#include<deque>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

template<typename T = int, template<typename> class Storage = std::deque>
class fifo{
    private:
    Storage<T> _que;
    public:
    using storage_type = Storage<T>;

    fifo() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~fifo()=default;
    void push(T t){
        _que.push_back(t);
    }
    fifo(const fifo& other): _que(other._que){}
    auto begin() const{
        return _que.begin();
    }
    auto end() const{
        return _que.end();
    }

    auto begin(){
        return _que.begin();
    }
    auto end(){
        return _que.end();
    }
    T get(){
        T temp=_que.front();
        _que.pop_front();
        return temp;
    }
    size_t size() const{
        return _que.size();
    }
    


};
using namespace std;
int main(){
    fifo<> ft;
    for(int i: {0,1,2,3,4})
        ft.push(i);

    fifo<int, std::deque> f = ft; //musi byc lonstruktor kopujancy

    std::cout << f.get() << "\n";
    std::cout << f.size() << "\n";

    for(fifo<>::storage_type::const_iterator i = f.begin(); i != f.end(); ++i)
        std::cout << *i << ",";

    std::cout << std::endl;
}
/*
  Wynik:
  fifo<T, StorageType>::fifo() [with T = int, StorageType = std::deque]
  0
  4
  1,2,3,4,
*/