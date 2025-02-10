#include "Vector.hpp"

int main(){
    
    Vector<int> vec;
    vec.push_back(3);
    vec.push_back(2); 
    vec.push_back(1);
    Vector<int> c(vec);
    Vector<int> a;
    std::cout<<"front: "<<vec.front()<<" back:"<<vec.back()<<std::endl;
    a.push_back(1);
    for(auto it=vec.begin();it!=vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    a=vec;
    vec.resize(1);
    Vector<int>::Iterator it(a.begin()+1);
    it=a.insert(it,2,4);
    a.show();
    it+=1;
    a.erase(it,a.end());
    a.show();
    c.show();
    vec.show();
    vec.pop_back();
    vec.show();
    c.pop_back();
    c.show();
    std::cout<<"exit"<<std::endl; 
    return 0;

}
