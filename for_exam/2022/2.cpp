#include <iostream>
#include <list>
#include <functional>

template <typename T, typename Function>
void print_to_if(std::ostream& os, T begin, T end, Function f){
    for( T it = begin; it!= end; it++){
        f(*it);
     }
    os<< std::endl;
}
template <typename T, typename Function>
void change(T begin, T end, Function f){
    for( T it = begin; it!= end; it++){
        f(*it);
     }
   
}
auto f1 = [](int x){ std::cout << " " << x; };
auto f2 = [](int x){ if (x % 2 == 0) { std::cout << x << " "; } };
auto f3(int add_value){
    return [add_value](int& x){ x += add_value; };
}

int main()
{
	const auto c1 = {1, 2, 3, 4, 5, 6, 7};

	print_to_if(std::cout << "All", begin(c1), end(c1), f1);
	print_to_if(std::cout << "Even", begin(c1), end(c1), f2);
	int arr[] = {1, 2, 3, 4, 5, 6, 7};
	print_to_if(std::cout << "Even", std::begin(arr), std::end(arr), f2);

	int add_value{-1}; //należy wykorzystać add_value do zmiany cl2
	std::list<int> cl2{7,6,5,4,3,2,1};
	change(begin(cl2), end(cl2), f3(add_value));
	//goto end;
	print_to_if(std::cout << "All", begin(cl2), end(cl2), f1);

	// end:
	return 0;
}

/* 
standardowe wyjście:
All: 1 2 3 4 5 6 7
Even: 2 4 6
All: 6 5 4 3 2 1 0
*/
