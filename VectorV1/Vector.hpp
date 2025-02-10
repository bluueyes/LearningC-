#include <complex>
#include <iostream>
#include <optional>
#include <cstring>

template<typename T>
class Vector{

private:
    T* data_;
    size_t size_;
    size_t capacity_;
    

public:


    Vector(int size=0):data_(nullptr),size_(size),capacity_(0){
        resever(size);
    }

    Vector(const Vector& vec):data_(nullptr),size_(vec.size_),capacity_(0){
        
        resever(size_);
      
        for(int i=0;i<size_;i++){

              data_[i]=vec.data_[i];
        }

    }

    Vector& operator=(const Vector& vec){
        if(this==&vec) return *this;

        size_=vec.size_;

        resever(size_);
      
        for(int i=0;i<size_;i++){

              data_[i]=vec.data_[i];
        }

        return *this;

    }

  
    ~Vector(){
        if(capacity_!=0){
          delete[] data_;
        }
        
        data_=nullptr;
    }

    void push_back(T value){
        if(size_>=capacity_){
            resever(size_);
        } 
        data_[size_++]=value;
    }

    void pop_back() {
        if(size_>0){
           size_--;
        }else{
          throw std::out_of_range("pop out of range");
        }
    }

    size_t size() const {
        return size_;
    }


    size_t capacity() const {
  
        return capacity_;    
    }

    

    T& operator[](int i){
        if( i>=size_ || i<0 ) throw std::out_of_range("[] out of range");
        return data_[i]; 
    }

    void show() const{
        std::cout<<"size = "<<size_<<"  capacity = "<<capacity_<<std::endl;
        for(int i=0;i<size_;i++){
          std::cout<<data_[i]<<" ";
        }  
        std::cout<<std::endl;
    }

    void resever(int size){

        if(size<capacity_){
          return ;
        }   

        while(capacity_ <= size){

            if(capacity_==0){
                capacity_+=1;
            }else{
                capacity_ *=2;  
            }
        }

        T* data=new T[capacity_];


        if(data_!=nullptr){

            if(typeid(T)!=typeid(int) && typeid(T)!=typeid(bool) && typeid(T)!=typeid(char)){

                for(int i=0;i<size_;i++){
                    data[i]=data_[i];
                }

            }else{
                std::memcpy(data,data_,sizeof(T)*size_);

            }

            delete[] data_;
        }
        
        data_=data;
    }

    void resize(int size){
        if(size<size_){
            size_=size;
            return;
        }

        if(size>capacity_){
            resever(size);
        } 

        size_=size; 
        
    }

    T& at(int i){
        if(i<0 || i>size_){
          throw std::out_of_range("index out of range");
        }

        return data_[i];
    }

    void clear(){
        size_=0;
    }
    
    T& front() const{
        if(size_<=0){
            throw std::logic_error("vector is empty!");
        }
        return data_[0]; 
    } 

    T& back() const{
        if(size_<=0){
            throw std::logic_error("vector is empty!");

        }

        return data_[size_-1];
    }

    void swap(Vector& other){

        T* data=other.data_;
        size_t size=other.size_;
        size_t capacity=other.capacity_;

        other.data_=data_;
        other.size_=size_;
        other.capacity_=capacity_;

        size_=size;
        capacity_=capacity;
        data_=data;

    }
   
    class Iterator{
    public:
        Iterator():data_ptr(nullptr){}
        Iterator(T* data):data_ptr(data){}
        Iterator(const Iterator& it):data_ptr(it.data_ptr){}
        ~Iterator(){}

        Iterator& operator++(){
         
            data_ptr+=1;
            return *this;
        }

        Iterator operator++(int){
            Iterator temp=*this;
            data_ptr+=1;
            return temp;
        }


        Iterator& operator--(){
            data_ptr-=1;
            return *this;
        }

        Iterator operator--(int){
            Iterator temp=*this;
            data_ptr-=1;
            return temp;
        }

        bool operator==(const Iterator& other)const{

            return other.data_ptr==data_ptr;
        }

        bool operator!=(const Iterator& other)const{
            return !(other==*this);
        }

        Iterator& operator+=(int i){
            
            data_ptr+=i;
            return *this;
        }

        Iterator& operator-=(int i){
            data_ptr-=i;
           return *this; 
        }


        Iterator operator-(int i){
            Iterator temp= *this;
            temp.data_ptr-=i;
            return temp ;
        }

        int operator -(const Iterator& it){
            return data_ptr-it.data_ptr;
        }

        Iterator operator+(int i){
            Iterator it=*this;
            it.data_ptr+=i;
            return it;
        }

        T& operator *(){
            return *data_ptr;
        } 

        T* operator ->(){

            return data_ptr;
        }


        T* data_ptr;

    };


    Iterator end(){
        return Iterator(data_+size_);
    }

    Iterator begin(){

        return Iterator(data_);
    }
    
    Iterator insert(Iterator& it,int n, T value){
        
        int pos=it-begin();    

        if(size_+n > capacity_){
            resever(size_+n);
        }

        for(int i=size_-1;i>=pos;i--){
            data_[i+n]=data_[i];

        }

        for(int i=pos;i<pos+n;i++){
            data_[i]=value;
        }
        size_+=n;

        return Iterator(data_+pos);
    }

    Iterator insert(Iterator& it,T value){
        return insert(it,1,value);
    }
    
    Iterator erase(Iterator it){
        
        if(it==end()){
            throw std::logic_error("out of range");
        }

        int pos = it-begin();
        for(int i=pos;i<size_-1;i++){
            data_[i]=data_[i+1];
        }

        size_--;
        return it;

        
    }

    Iterator erase(Iterator begins,Iterator ends){
    

    int num=ends-begins;
    int pos = begins-begin();
    for(int i=pos;i<size_-num-1;i++){
        data_[i]=data_[i+num];
    }

    size_-=num;
    return begins;

        
    }
};
