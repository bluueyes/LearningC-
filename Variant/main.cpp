#include "Variant.h"
#include <string>
#include <iostream>

int main(){
  Variant<std::string,int> v(std::string("hello"));
  v.visit([](auto v){
          std::cout<<v<<std::endl;
      });       
  auto s=v.get<std::string>();
  std::cout<<s<<std::endl;

  std::cout<<v.holds_alternative<std::string>()<<std::endl; 
  return 0;
}
