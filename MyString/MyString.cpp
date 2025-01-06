#include "MyString.h"
#include <cstring>

MyString::MyString(const char* data){
    if(data==nullptr){
        data=nullptr;
        return;
    }

    _len=strlen(data);
    _data=new char[_len+1];

    memcpy(_data,data,_len);
    _data[_len]='\0';

}

MyString::MyString(const MyString& str){

    if(str._data==nullptr){
        _data==nullptr;
        _len=0;
        return;
    }

    _len=str._len;

    if(_data!=nullptr)
    {
        delete[] _data;
    }

    _data=new char[_len+1];
    memcpy(_data,str._data,_len);
    _data[_len]='\0';

}

MyString& MyString::operator=(const MyString& str){

    if(this==&str){
        return *this;
    }

    _len=str._len;
    if(_data!=nullptr){
        delete[] _data;
    }

    _data=new char[_len+1];
    memcpy(_data,str._data,_len);
    _data[_len]='\0';

    return *this;
}

MyString::MyString(MyString&& str){

    if(str._data==nullptr){
        _data=nullptr;
        _len=0;
        return;
    }

    if(_data!=nullptr){
        delete[] _data;
    }
    _data=str._data;
    _len=str._len;

    str._data=nullptr;
    str._len=0;

}

MyString& MyString::operator=(MyString&& str){
    if(this==&str){
        return *this;
    }

    _data=str._data;
    _len=str._len;

    str._data=nullptr;
    str._len=0;
    return *this;
}

MyString MyString::operator+(const MyString& str){

    size_t len=strlen(str._data)+_len;
    char* _str=new char[len+1];

    memcpy(_str,_data,_len);
    memcpy(_str+_len,str._data,str._len);
    _str[len]='\0';
    return MyString(_str);
}

MyString& MyString::operator+=(const MyString& str){

    size_t len=strlen(str._data)+_len;
    char* _str=new char[len+1];
    memcpy(_str,_data,_len);
    memcpy(_str+_len,str._data,str._len);
    _str[len]='\0';

    _data=_str;
    return *this;
}

bool MyString::operator==(const MyString& str){

    return strcmp(_data,str._data)==0;
}

int MyString::Size(){
    return _len;
}

MyString::~MyString(){

    std::cout<<"MyString destruct!"<<std::endl;
    if(_data!=nullptr){
        delete[] _data;
    }
}

std::ostream& operator<<(std::ostream& out,const MyString& str){

    out<<str._data;
    return out;
}



int main(){
    MyString str1("Hello, World!");
    MyString str2 = str1; // 拷贝构造
    MyString str3;
    str3 = str1; // 赋值运算符重载
    str3+=str2;

    MyString str4("Hello Bluue");
   MyString str5=std::move(str4);  //移动构造

    if(str4.Empty()){
        std::cout<<" str4 == Empty"<<std::endl;
    }else{
       std::cout << "str4: " << str4 << std::endl; 
    }

    std::cout << "str1: " << str1 << std::endl;
    std::cout << "str2: " << str2 << std::endl;
    std::cout << "str3: " << str3 << std::endl;
    std::cout << "str5: " << str5 << std::endl;

    if (str1 == str2) {
        std::cout << "str1 and str2 are equal." << std::endl;
    } else {
        std::cout << "str1 and str2 are not equal." << std::endl;
    }

    return 0;
}