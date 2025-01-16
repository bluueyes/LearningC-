#include <iostream>

template <typename T>
class Vector{
public:
    Vector(size_t capacity=10):_capacity(capacity),_size(0),buffer(nullptr){
        resize(capacity);
        
    }
    Vector(size_t size,T value):_capacity(size*2),_size(size),buffer(nullptr){
        resize(_capacity);
        for(int i=0;i<size;i++){
            buffer[i]=value;
        }

    }

    ~Vector(){  
        clearBuffer();
    }

    Vector(const Vector& other):_size(other._size),buffer(nullptr){
        if(other._size==0){
            resize(other._capacity);
            return;
        }

        _capacity=other._capacity;
        resize(_capacity);
        for(int i=0;i<_size;i++){
            buffer[i]=other.buffer[i];
        }

    }

    Vector& operator=(const Vector& other){
        if(&other==this){
            return *this;
        }

        clearBuffer();
        if(other._size==0){
            _size=0;
            buffer=nullptr;
            resize(other._capacity);
        }

        _size=other._size;
        resize(other._capacity);
        for(int i=0;i<_size;i++){
            buffer[i]=other.buffer[i];
        }
        return *this;
    }

    Vector(Vector&& other):_size(other._size),_capacity(other._capacity),buffer(other.buffer){
        other.buffer=nullptr;
        other._size=0;
        return;
    }

    Vector& operator=(Vector&& other){
        if(&other==this){
            return *this;
        }
        _size=other._size;
        _capacity=other._capacity;
        buffer=other.buffer;

        other._size=0;
        other.buffer=nullptr;
        return *this;
    }

    void push_back(T value){
        if(_size==_capacity){
            resize(_capacity*2);
        }
        buffer[_size++]=value;
        return;
    }

    void pop_back(){
        _size--;        
    }

    void insert(size_t count,T value){
        if(count>_size) return;
        if(_size==_capacity){
            resize(_capacity*2);
        }
        for(int i=_size-1;i>=count;i--){
            buffer[i+1]=buffer[i];
        }
        buffer[count]=value;
        _size++;
    }

    void reserver(size_t size){
        resize(size);
    }

    void clear(){
        _size=0;
    }

    size_t capacity(){
        return _capacity;
    }

    size_t size(){
        return _size;
    }


    class Iterator{
    public:
        using Reference = T&;
        using Pointer= T*;

        Iterator(Vector<T>* ptr,size_t position):_ptr(ptr),pos(position),end(ptr->_size){

        }

        Pointer operator->(){
            return &(_ptr->buffer[pos]);
        }

        Reference operator*(){
            return _ptr->buffer[pos];
        }

        Iterator& operator++(){
            if(pos==end) throw std::out_of_range("error ++");
            pos++;
            return *this;
        }

        Iterator operator++(int ){
            if(pos==end) throw std::out_of_range("error ++");
            Iterator temp = *this;
            pos++;
            return temp;
        }

        Iterator& operator--(){
            if(pos==0) throw std::out_of_range("error --");
            pos--;
            return *this;
        }

        Iterator operator--(int ){
            if(pos==0) throw std::out_of_range("error --");
            Iterator temp = *this;
            pos--;
            return temp;
        }

        bool operator==(const Iterator& other){
            return (_ptr==other._ptr)&&(pos==other.pos);
        }

        bool operator!=(const Iterator& other){
            return !(*this==other);
        }

    private:
        Vector<T>* _ptr;
        size_t pos;
        size_t end;
    };

    Iterator begin(){
        return Iterator(this,0);
    }

    Iterator end(){
        return Iterator(this,_size);
    }

private:
    size_t _size;
    size_t _capacity;
    T* buffer;

    void resize(size_t capacity){
        if(capacity==0){
            _capacity=0;
            return;
        }
        T* new_buffer = new T[capacity];

        if(buffer!=nullptr){
            for(size_t i=0;i<_size;i++){
                new_buffer[i]=buffer[i];
            }
                        
            delete[] buffer;
        }
        _capacity=capacity;
        buffer=new_buffer;

    }

    void clearBuffer(){
        if(buffer==nullptr){
            return;
        }
        delete[] buffer;
        buffer=nullptr;
        _size=0;
    }
};