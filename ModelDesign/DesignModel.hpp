#include <iostream>
#include <optional>
#include <vector>
#include <memory>

//策略模式

//Reduce用来抽象处理函数的方法
struct Reduce{

  Reduce()=default;
  virtual int init()=0;
  virtual int add(int res,int value)=0;
};


struct SumReduce:public Reduce{
  
  int init() override{
    return 0;
  }

  int add(int res,int value) override{
    res+=value;
    return res;
    
  }

};


struct ProductReduce:public Reduce{

  int init() override{
    return 1;
  }

  int add(int res,int value)override{
    res*=value;
    return res;
  }

};


struct Input{

  virtual std::optional<int> fetch()=0;

};


struct VecInput:public Input{

  std::vector<int> vec;
  int pos=0;
  
  VecInput(std::vector<int> v):vec(v){}

  std::optional<int> fetch() override{
    if(pos==vec.size()) {return std::nullopt;};

    return vec[pos++];
 
  }
};


struct CinInput:public Input{
  
  std::optional<int> fetch() override{

    int temp;
    std::cin>>temp;
    if(temp==-1) {return std::nullopt;}
    
    return temp;
  }
};


// ============================================================
//工厂模式
// ============================================================

struct ReduceState{

  virtual void add(int val)=0;
  virtual int result()=0;
};

struct SumReduceState:public ReduceState{
  int value=0;
  SumReduceState():value(0){}

  void add(int val) override{
    value+=val;  
  }

  int result() override{
    return value;
  }

};


struct ProductReduceState:public ReduceState{
  int value;
  ProductReduceState():value(1){}

  void add(int val) override{
    value+=val;  
  }

  int result() override{
    return value;
  }

};

struct AvergeReduceState:public ReduceState{
  int value;
  int count;
  AvergeReduceState():value(0),count(0){}

  void add(int val) override{
    value+=val;  
    count++;
  }

  int result() override{
    int ret = value / count;
    return ret;
  }
};

 
struct Reduces{
  virtual std::unique_ptr<ReduceState> init()=0;
};

struct SumReduces:public Reduces{
  std::unique_ptr<ReduceState> init() override{

    return std::make_unique<SumReduceState>();
  }
}; 

struct ProductReduces:public Reduces{
  std::unique_ptr<ReduceState> init() override{

    return std::make_unique<ProductReduceState>();
  }
}; 

struct AvergeReduces:public Reduces{
  std::unique_ptr<ReduceState> init() override{

    return std::make_unique<AvergeReduceState>();
  }
};



