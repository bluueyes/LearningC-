#include <iostream>
#include <atomic>

struct ControlBlock{

    std::atomic<int> ref_count;
    ControlBlock():ref_count(1){

    }
};

template<typename T>
class SharePtr{

public:
    SharePtr():_ptr(nullptr),_block(nullptr){};
    explicit SharePtr(T* ptr);
    ~SharePtr();
    SharePtr(const SharePtr& ptr);
    SharePtr& operator=(const SharePtr& ptr) noexcept;
    SharePtr(SharePtr&& ptr);
    SharePtr& operator=(SharePtr&& ptr) noexcept;
    T* operator->();
    T& operator*();
    int getRefCount() const;
    T* get() const;
    void reset(T* p = nullptr);
    
private:
    void Clear();
    ControlBlock* _block;
    T* _ptr;
};


template<typename T>
SharePtr<T>::SharePtr(T* ptr):_ptr(ptr){
    if(_ptr==nullptr){
       _block=nullptr; 
    }else{
        _block=new ControlBlock();
    }
}

template<typename T>
void SharePtr<T>::Clear(){
    if(_block){
        --_block->ref_count;
        if(_block->ref_count==0){
            delete _block;
           _block=nullptr;
            delete _ptr;
            _ptr=nullptr;
        }
    }

}


template<typename T>
SharePtr<T>::~SharePtr(){
    if(_ptr){
        Clear();
    }else{
        _block=nullptr;
    }
}

template<typename T>
SharePtr<T>::SharePtr(const SharePtr<T>& ptr):_ptr(ptr._ptr),_block(ptr._block){
    if(_block)
    ptr._block->ref_count++;

}

template<typename T>
SharePtr<T>& SharePtr<T>::operator=(const SharePtr<T>& ptr) noexcept{
    if(this==&ptr){
        return *this;
    }
    Clear();
    _ptr=ptr._ptr;
    _block=ptr._block;
    if(_block!=nullptr){
        _block->ref_count++;
    }
    return *this;
}

template<typename T>
SharePtr<T>::SharePtr(SharePtr<T>&& ptr):_ptr(ptr._ptr),_block(ptr._block){

    ptr->_block=nullptr;
    ptr->_ptr=nullptr;

}

template<typename T>
SharePtr<T>& SharePtr<T>::operator=(SharePtr<T>&& ptr) noexcept{
    if(this==&ptr){
        return *this;
    }
    Clear();
    _ptr=ptr->ptr;
    _block=ptr->_block;
    ptr->_block=nullptr;
    ptr->_block=nullptr;

    return *this;
}

template<typename T>
T* SharePtr<T>::operator->(){
    return _ptr;
}

template<typename T>
T& SharePtr<T>::operator*(){
    return *this;
}

template<typename T>
int SharePtr<T>::getRefCount() const{
    return _block ? _block->ref_count.load() : 0 ;
}

template<typename T>
T* SharePtr<T>::get() const{
    return _ptr;
}

template<typename T>
void SharePtr<T>::reset(T* p){
    Clear();
    _ptr=p;
    if(p){
        _block=new ControlBlock();

    }else{
        _block=nullptr;
    }
}