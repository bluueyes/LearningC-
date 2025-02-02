#include "DesignModel.hpp"

//策略模式测试案例
int reduce(Input* input,Reduce* reduce){

  int res=reduce->init();
  std::optional<int> temp=input->fetch();
  while(temp.has_value()){
    
    res=reduce->add(res,temp.value());
    temp=input->fetch();
  }
  std::cout<<res<<std::endl;
  return res;
}
//策略模式测试代码
void testStrate(){
  std::vector<int> vec{12,3,4,5};
  reduce(new VecInput(vec),new SumReduce());
  reduce(new VecInput(vec),new ProductReduce());
  reduce(new CinInput(),new SumReduce());
  reduce(new CinInput(),new ProductReduce());
}


//工厂模式测试案例
int reduce1(Input* input,Reduces* reduce){
  std::unique_ptr<ReduceState> state = reduce->init(); 
  while(auto val=input->fetch()){
    state->add(val.value());
  }
  std::cout<<state->result()<<std::endl;
  return state->result();
}
void testStrate1(){
  std::vector<int> vec{2,3,4,5};
  reduce1(new VecInput(vec),new SumReduces());
  reduce1(new VecInput(vec),new ProductReduces());
  reduce1(new VecInput(vec),new AvergeReduces());
}
int main(){
  testStrate1();
  return 0;
}
