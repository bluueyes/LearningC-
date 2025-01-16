#include "Vector.h"

int main(){

    Vector<std::string> vec(10,"hello");

    vec.push_back("world");
    vec.push_back("peal");
    vec.push_back("watemelon");

    for(Vector<std::string>::Iterator it=vec.begin(); it != vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"size="<<vec.size()<<" capacity="<<vec.capacity()<<std::endl;
    vec.pop_back();
    std::cout<<"size="<<vec.size()<<" capacity="<<vec.capacity()<<std::endl;

    for(Vector<std::string>::Iterator it=vec.begin(); it != vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    vec.insert(3,"peach");


    for(Vector<std::string>::Iterator it=vec.begin(); it != vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    Vector<std::string> vec2=vec;
    vec2.insert(4,"apple");

    std::cout<<"拷贝构造"<<std::endl;
    for(Vector<std::string>::Iterator it=vec2.begin(); it != vec2.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    Vector<std::string> vec3(3,"world");
    for(Vector<std::string>::Iterator it=vec3.begin(); it != vec3.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    
    vec3 = vec2;
    std::cout<<"拷贝赋值"<<std::endl;
    for(Vector<std::string>::Iterator it=vec3.begin(); it != vec3.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;


    Vector<std::string> vec4=std::move(vec3);
    std::cout<<"移动构造"<<std::endl;
    for(Vector<std::string>::Iterator it=vec4.begin(); it != vec4.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    vec4=std::move(vec);
    std::cout<<"移动赋值"<<std::endl;
    for(Vector<std::string>::Iterator it=vec4.begin(); it != vec4.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    std::cout<<" end "<<std::endl;

}