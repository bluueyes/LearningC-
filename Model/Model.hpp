#include <iostream>
#include <type_traits>
// template<typename T>
// struct ArgType{
//     using type=const T&;
// };

//模板偏特化
// template<typename T>
// struct ArgType<T*>{
//     using type= T*;
// };

// template<>
// struct ArgType<int>{
//     using type = int;
// };

// template<>
// struct ArgType<double>{
//     using type = double;
// };

// template<>
// struct ArgType<char>{
//     using type=char;
// };

// template<typename T>
// using ArgType_t = typename ArgType<T>::type;


// template<typename T>
// void Show(ArgType_t<T> t){
//     std::cout<<t<<std::endl;
// }


//enable_if_t 实现
template<bool Cond,typename T>
struct enable_if{
    
};

template<typename T>
struct enable_if<true,T>{
    using type=T;
};

template<bool Cond,typename T>
using enable_if_t = typename enable_if<Cond,T>::type;


template<typename T>
struct IsLessThanPtr{
    constexpr static bool value = (sizeof(T)<=sizeof(void*));
};

template<typename T>
struct NotLess{
    constexpr static bool value = (!IsLessThanPtr<T>::value);
};

template <typename T>
constexpr bool IsLessThanPtr_v = IsLessThanPtr<T>::value;

template <typename T>
constexpr bool IsLargetThanPtr_v = NotLess<T>::value;

template<typename T>
void f(enable_if_t<IsLessThanPtr_v<T>,T>){

    std::cout<< " 1 "<<std::endl; 

}

template<typename T>
void f(enable_if_t<IsLargetThanPtr_v<T>,T>){
    std::cout<< " 2 " <<std::endl;
}

struct A{
    int arr[100];
    A()=default;
    A& operator=(const A&)=default;
};

struct B{
    int a;
    B()=default;
    B& operator=(const B& )=default;
};

template<typename T>
int sum(const T& t){
    return t;
}
//嵌套展开
template<typename T,typename... Args>
T sum(const T& t,const Args&... args){
    return t+sum(args...);
}



//自定义展开(折叠表达式)


//一元展开
template <typename ...Args>
auto mutil(Args... args){

    return (...-args);
}

//二元展开
template<typename ...Args>
void Print(const Args&... args){

    (std::cout<<...<<args)<<std::endl;
}

struct st{
    int a;
    st(int a):a(a){};
    void method() const{
        std::cout<<"st call method"<<std::endl;
    }
};

template <typename T>
std::enable_if_t<std::is_void_v<std::void_t<decltype(std::declval<std::remove_reference_t<T>>().method())>>,void>
f(const T& t){
    t.method();
}


//forward

struct Alloc{
    uint8_t buf[2048]={0};
    uint8_t* pos=buf;
    void* operator()(size_t size){
        auto tmp=pos;
        pos+=size;
        return tmp;
    }
};

// template<typename T>
// T&& Forward(T&& t){
//     std::cout<<" rightRemove "<<std::endl;
//     return static_cast<T &&>(t);
// }

// template<typename T>
// T&& Forward(T& t){
//     std::cout<<" leftRemove "<<std::endl;
//     return static_cast<T &&>(t);
// }

template <typename T>
constexpr T&& Forward(typename std::remove_reference_t<T>& t){

    return static_cast<T&&>(t);
} 

template <typename T>
constexpr T&& Forward(typename std::remove_reference_t<T>&& t){

    return static_cast<T&&>(t);
} 

template<typename T,typename... Args>
T* Create(Args&&... args){
    Alloc alloc;
    T* ret=static_cast<T*>(alloc(sizeof(T)));
    return new(ret) T(Forward<Args>(args)...); //右值引用传递过程会失去右性
    
}

struct Point{
    int _x,_y;
    Point(int x, int y):_x(x),_y(y){}

    void Show(){
        std::cout<<" x = "<<_x<<" y = "<<_y<<std::endl;
    }
};

void Demo(){
    A a;
    B b;
    f<A>(a);    //2 
    f<B>(b);    //1

    int ret=sum<int,int,int>(1,2,3);
    std::cout<< ret <<std::endl;

    Print("123","456","hello");

    auto ret1=mutil(3,2,1,2);
    std::cout<<ret1<<std::endl;

    st s(2);
    f(s);

    auto res=Forward<int>(5);    //右值引用

    int d=5;
    int& data=Forward<int &>(d);

    std::cout<<"==============================="<<std::endl;
    Point* p = Create<Point,int,int>(3,4);
    p->Show();
}
