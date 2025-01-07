#include <iostream>

class MyString{

public:
    MyString():_data(nullptr),_len(0){}
    MyString(const char* data);
    MyString(const MyString& str);
    MyString& operator=(const MyString& str);
    MyString(MyString&& str);
    MyString& operator=(MyString&& str);

    MyString operator+(const MyString& str);
    MyString& operator+=(const MyString& str);
    bool operator==(const MyString& str);
    friend std::ostream& operator<<(std::ostream& out,const MyString& str);
    ~MyString();
    int Size();
    inline bool Empty() const{
        return _data==nullptr;
    }
    

private:
    char* _data;
    size_t _len;
};