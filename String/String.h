#include <iostream>

class String{

public:
    String();
    String(const char* data);
    

private:
    char* _data;
    size_t _size;
};

String::String():_data(nullptr),_size(0){}