#include <iostream>
#include<vector>
// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.
namespace OOP{
    template<typename T>
    class Array{
        private:
        std::vector<T> _data;
        int _size;
        public:
        Array(int size): _size(size){
            _data.reserve(size);
        }
        ~Array()=default;
        using value_type = T;
        Array& insert(T t){
            _data.push_back(t);
            return *this;
        }
        T& operator[](int i) {
            return _data[i];
        }
        
        Array& operator%(T val) {
            _data.push_back(val);
            return *this;
        }
        unsigned operator~() const{
            return _data.size();
        }
    };

};

int main()
{
    typedef ::OOP::Array<int> type;
    type a(rand() % 100 + 10); // nie trzeba seedować żeby program się wykonał

    a.insert('#' - 1).insert('P') % type::value_type('O') % ('-') % ('E') % ('G') % ('Z') % ('1');

     ++a[0];
    for (unsigned i = 0; i != ~a; i++){
        std::cout << static_cast<char>(a[i]) << (i + 1 != ~a ? '_' : '\n');
    }
}
//#_P_O_-_E_G_Z_1