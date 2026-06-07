#include<iostream>
#include<array>
#include<string>
#include <memory>


// Program ma wytworzyć poniższy output.
// Program ma nie leakować pamięci.
// Kod można pisać tylko w wyznaczonych miejscach.

void my_print_el(const std::string &s){
    std::cout<<s;
}
void my_swap(int &a, int &b){
    int temp=a;
    a=b;
    b=temp;
}
void my_swap(std::unique_ptr<int> &p1,std::unique_ptr<int> &p2){
    int temp=*p1;
    *p1=*p2;
    *p2=temp;
}
template<size_t N>
void my_print(const std::array<std::unique_ptr<int>,N> &obj, const std::string &s1=";",const std::string &s2="\n" ){
    std::cout<<"[ ";
    for( size_t i=0; i <N; i++ ){
        std::cout<<*obj[i]<<s1;
    }
    std::cout<<" ]"<<s2;
    
}
int main()
{
  std::array<std::unique_ptr<int>,2> a = {
      std::unique_ptr<int>(new int {1}),
      std::unique_ptr<int>(new int {2})
      };

  my_print_el("----------------\n");
  my_print(a,";"," -> ");
  my_swap(a[0],a[1]);
  my_print(a,";"," -> ");
  my_swap(*a[0],*a[1]);
  my_print(a);
  my_print_el("----------------");
}
//[1;2;] -> [2;1;] -> [1;2;]