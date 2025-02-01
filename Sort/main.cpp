#include "sort.h"
#include <iostream>
#include <vector>

int main(){

  std::vector<int> v{1,4,1,72,3,5,774,43,33};
  radixSort(v);
  std::cout<<"基数排序"<<std::endl;
  for(auto& a:v){
    std::cout<<a<<" ";
  }
  std::cout<<std::endl;
  return 0; 
  
}

