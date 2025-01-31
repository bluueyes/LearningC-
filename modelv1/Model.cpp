
#include <iostream>
#include <string>
#include <vector>

template<template<typename ,typename >class Container,typename T>
class ContainerPrinter {
public:
  void print(const Container<T,std::allocator<T>>& container)
  {
    for(const auto& elem:container){
      std::cout<<elem<<" ";

    }
    std::cout<<std::endl;
    
  }
private:
  
};

template<typename T,typename U>
class Pointer{
public:
  void print(T a, U b){
  std::cout<<"pointer : "<<a<<" "<<b<<std::endl;
  }
};
  
template<typename T,typename U>
class Pointer<T,U*>{
public:
  void print(T a ,U* b ){
  std::cout<<"pointer: "<< a <<" "*b<<std::endl;
}
};

template<typename... Args>
  auto printAll(Args... args)->decltype((args+ ...)){

   return (args + ...);
}


int main(){
  
  std::vector<int> a{1,2,3,4,5,6};
  ContainerPrinter<std::vector,int> p;
  p.print(a);

  Pointer<int,int> s;
  s.print(1,2);
  auto b=printAll(3,2.0f,2.3);
  
  std::cout<<b<<std::endl;
  return 0;
}
