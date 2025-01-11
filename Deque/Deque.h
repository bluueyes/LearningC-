#include <iostream>



template <typename T>
class Deque{
private:
    T* buffer;
    size_t capacity;    // 容量
    size_t front_idx;   // 头指针
    size_t back_idx;   // 尾指针
    size_t count;       // 元素个数

    void resize(size_t new_capacity){
        T* new_buffer=new T[new_capacity];
        for(size_t i=0;i<count;++i){
            new_buffer[i]=buffer[(front_idx+i)%capacity];
        }

        delete[] buffer;
        buffer=new_buffer;
        front_idx=0;
        back_idx=count;
        capacity=new_capacity;

    }
public:
    Deque(int capacity=10):capacity(capacity),front_idx(0),back_idx(0),count(0){
        buffer=new T[capacity];
    }

    //析构函数
    ~Deque(){
        delete[] buffer;
    }

    //判断是否为空
    bool empty() const{
        return count==0;
    }

    //返回元素个数
    size_t size() const{
        return count;
    }

    //返回队首元素
    T front() const{
        return buffer[front_idx];

    }

    //返回队尾元素
    T back() const{
        return buffer[(back_idx-1+capacity)%capacity];
    }

    //头部插入元素
    void push_front(const T& value){
        if(count==capacity){
            resize(capacity*2); 
        }

        front_idx=(front_idx-1+capacity)%capacity;
        buffer[front_idx]=value;
        ++count;
    }

    //尾部插入元素
    void push_back(const T& value){
        if(count==capacity){
            resize(capacity*2);
        }

        buffer[back_idx]=value;
        back_idx=(back_idx+1)%capacity;
        ++count;

    }

    //头部删除元素
    void pop_front(){
        if(empty()){
            return;
        }

        front_idx=(front_idx+1)%capacity;
        --count;
    }

    void pop_back(){
        if(empty()){
            return;
        }

        back_idx=(back_idx-1+capacity)%capacity;
        --count;
    }

    //打印队列
    void print(){
        for(size_t i=0;i<count;++i){
            std::cout<<buffer[(front_idx+i)%capacity]<<" ";
        }
        std::cout<<std::endl;
    }

    //清空队列
    void clear(){
        front_idx=0;
        back_idx=0;
        count=0;
    }

    //插入元素
    void insert(size_t pos,const T& value){
        if(count==capacity){
            resize(capacity*2);
        }

        for(size_t i=0;i<count-pos;++i){
            buffer[((front_idx+count)%capacity+capacity-i)%capacity]=buffer[((front_idx+count)%capacity-i-1+capacity)%capacity];

        }
        buffer[front_idx+pos]=value;
        back_idx=(back_idx+1)%capacity;
        ++count;
    }

    class Iterator{
    private:
        Deque<T>* deque_ptr;
        size_t pos;

    public:
        using iterator_category=std::bidirectional_iterator_tag;
        using value_type=T;
        using difference_type=std::ptrdiff_t;
        using pointer=T*;
        using reference = T&;

        Iterator(Deque<T>* deque,size_t position):deque_ptr(deque),pos(position){

        }

        //解引用操作
        reference operator*() const{
            
            size_t real_idx=(deque_ptr->front_idx+pos)%deque_ptr->capacity;
            return deque_ptr->buffer[real_idx];
        }

        //指针操作
        pointer operator->() const{

            size_t real_idx=(deque_ptr->front_idx+pos)%capacity;
            return &(deque_ptr->buffer[real_idx]);
        }

        //前置递增
        Iterator& operator++(){
            ++pos;
            return *this;
        }

        //后置递增
        Iterator operator++(int){
            
            Iterator temp=*this;
            ++pos;
            return temp;
        }

        //前置递减
        Iterator& operator--(){
           --pos;
           return *this;
        }

        //后置递减
        Iterator operator--(int){
            Iterator temp=*this;
            --pos;
            return temp;
        }

        bool operator==(const Iterator& other) const{

            return (deque_ptr==other.deque_ptr)&&(pos==other.pos);
        }

        bool operator!=(const Iterator& other) const{
            return !(*this==other);
        }

    };

    //获取Begin迭代器
    Iterator begin(){
        return Iterator(this,0);
    }

    //获取end迭代器
    Iterator end(){
        return Iterator(this,count);
    }

};

