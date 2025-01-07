#include <iostream>

class Baseclass
{

public:
    Baseclass() : a(1024) {}
    virtual void f() { std::cout << "Base::f" << std::endl; }
    virtual void g() { std::cout << "Base::g" << std::endl; }
    virtual void h() { std::cout << "Base::h" << std::endl; }
    int a;
};

// 0 1 2 3   4 5 6 7(虚函数表空间)    8 9 10 11 12 13 14 15(存储的是a)

class DeriveClass : public Baseclass
{
public:
    virtual void f() { std::cout << "Derive::f" <<std::endl;}
    virtual void g2() { std::cout << "Derive::g2" << std::endl; }
    virtual void h3() { std::cout << "Derive::h3" << std::endl; }
};