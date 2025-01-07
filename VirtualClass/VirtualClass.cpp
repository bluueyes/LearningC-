#include "VirtualClass.h"

typedef void(*Func)(void*);

void VirtualTable(){

    Baseclass base;
    std::cout<<"baseClass size is "<<sizeof(base)<<std::endl;

    void** vf=*(void***)(&base);

    Func fc=Func(vf[0]);
    fc(&base);

    Func fc1=Func(vf[1]);
    fc1(&base);
    
    Func fc2=Func(vf[2]);
    fc2(&base);

    char* data=(char*)(&base);

    std::cout<<"base class value is "<<*(int*)(data+sizeof(void*))<<std::endl;
    return;
}

void VirtualTableTest(){

    Baseclass*derive=new DeriveClass();

    std::cout<<"derive Class size is "<<sizeof(*derive)<<std::endl;

    void** vf=*(void***)derive;

    Func fc=Func(vf[0]);
    fc(&derive);

    Func fc1=Func(vf[1]);
    fc1(&derive);
    
    Func fc2=Func(vf[2]);
    fc2(&derive);


    Func fc3=Func(vf[3]);
    fc3(&derive);

    Func fc4=Func(vf[4]);
    fc4(&derive);
    
    char* data=(char*)(derive); 
    std::cout<<"derive class value is "<<*(int*)(data+sizeof(void*))<<std::endl;
}

int main(){

    VirtualTable();
    VirtualTableTest();
    return 0;
}