#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <functional>

//HashNode结构
template<typename Key, typename T>
struct HashNode{
    std::pair<Key,T> data;
    HashNode* next;
    HashNode(const Key& key,const T& value):data(std::make_pair(key,value)),next(nullptr){
    }
};

template<typename Key,typename T,typename Hash=std::hash<Key>>
class HashMap
{
public:
    //前向声明迭代器
    class Iterator;

    //类型定义
    using key_type=Key;
    using mapped_type=T;
    using value_type=std::pair<Key,T>;
    using size_type=size_t;

    HashMap(size_type initial_capacity=16,double max_load_factor=0.75);
    ~HashMap();

    //禁用拷贝和赋值
    HashMap(const HashMap& )=delete;
    HashMap& operator=(const HashMap& )=delete;

    //基本操作
    void insert(const Key& key,const T& valule);
    T* find(const Key& key);
    bool erase(const Key& key);
    size_type size() const;
    bool empty() const;
    void clear();

    //迭代器操作
    Iterator begin();
    Iterator end();

    //迭代器类
    class Iterator{
    public:
        //迭代器别名
        using iterator_category=std::forward_iterator_tag;
        using value_type=std::pair<Key,T>;
        using difference_type=std::ptrdiff_t;
        using pointer=value_type*;
        using reference=value_type&;

        Iterator(HashMap* map,size_type bucket_index, HashNode<Key,T>* node);

        reference operator*() const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        HashMap* map_;
        size_type bucket_index;
        HashNode<Key,T>* current_node;

        //移动到下一个
        void advance();
    };

private:
    std::vector<HashNode<Key,T>*> buckets_;
    size_type bucket_count;
    size_type element_count;
    double max_load_factor;
    Hash hash_func;

    void rehash();
};

template <typename Key,typename T,typename Hash>
HashMap<Key,T,Hash>::HashMap(size_type initial_capacity,double max_load_factor)
    :max_load_factor(max_load_factor),bucket_count(initial_capacity),element_count(0),hash_func(Hash()){

    buckets_.resize(bucket_count,nullptr);

}

template<typename Key,typename T,typename Hash>
HashMap<Key,T,Hash>::~HashMap(){
    
    clear();
}

//基本操作
template<typename Key,typename T,typename Hash>
void HashMap<Key,T,Hash>::insert(const Key& key,const T& value){

    size_type hash_value=hash_func(key);
    size_type index=hash_value % bucket_count;

    HashNode<Key,T>* node=buckets_[index];
    while(node!=nullptr){
        if(node->data.first==key){
            node->data.second=value;
            return;
        }
        node=node->next;
    }

    //键不存在,采用头插法
    HashNode<Key,T>* new_node=new HashNode(key,value);
    new_node->next=buckets_[index];
    buckets_[index]=new_node;
    ++element_count;

    //检查负载因子，是否需要扩容
    double load_factor=static_cast<double>(element_count)/bucket_count;
    if(load_factor>max_load_factor) {
        rehash();
    }
}


template<typename Key,typename T,typename Hash>
T* HashMap<Key,T,Hash>::find(const Key& key){
    size_type hash_value = hash_func(key);
    size_type index = hash_value % bucket_count;

    HashNode<Key,T>* node=buckets_[index];
    while(node!=nullptr){
        if(node->data.first==key){
            return &(node->data.second);
        }
        node=node->next;
    }
    return nullptr;

}

template<typename Key,typename T,typename Hash>
bool HashMap<Key,T,Hash>::erase(const Key& key){
    size_type hash_value=hash_func(key);
    size_type index=hash_value%bucket_count;

    HashNode<Key,T>* node=buckets_[index];
    HashNode<Key,T>* prev=nullptr;
    while(node!=nullptr){
        if(node->data.first==key){
            if(prev==nullptr){
                buckets_[index]=node->next;
            }else{
                prev->next=node->next;
            }
            delete node;
            --element_count;
            return true;
        }
        prev=node;
        node=node->next;
    }
    return false;
}

template<typename Key,typename T,typename Hash>
size_t HashMap<Key,T,Hash>::size() const{
    return element_count;
}

template<typename Key,typename T,typename Hash>
bool HashMap<Key,T,Hash>::empty() const{
    return element_count==0;
}

template<typename Key,typename T,typename Hash>
void HashMap<Key,T,Hash>::clear(){
    for(size_type i=0;i<bucket_count;i++){
        HashNode<Key,T>* node=buckets_[i];
        while(node!=nullptr){
            HashNode<Key,T>* temp=node;
            node=node->next;
            delete temp;
        }
        buckets_[i]=nullptr;
    }
    element_count=0;
}

template<typename Key,typename T,typename Hash>
void HashMap<Key,T,Hash>::rehash(){
    
    size_type new_bucket_count = bucket_count*2;
    std::vector<HashNode<Key,T>*> new_buckets;
    
    //重新分配所有元素
    for(size_type i =0; i<bucket_count ;i++){
        HashNode<Key,T>* node=buckets_[i];
        while(node!=nullptr){
            HashNode<Key,T>* next_node=node->next;
            
            size_type new_index=hash_func(node->data.first) % new_bucket_count;


            //插入到新桶的头部
            node->next=new_buckets[new_index];
            new_buckets[new_index] = node;

            node=next_node;
        }

    }

    //替换旧桶
    buckets_=std::move(new_buckets);
    bucket_count=new_bucket_count;
}

template<typename Key,typename T,typename Hash>
HashMap<Key,T,Hash>::Iterator::Iterator(HashMap* map,size_type bucket_index, HashNode<Key,T>* node)
:map_(map),bucket_index(bucket_index),current_node(node){

}


template<typename Key,typename T,typename Hash>
typename HashMap<Key,T,Hash>::Iterator::reference 
HashMap<Key,T,Hash>::Iterator::operator*() const{
    if(current_node==nullptr){
        throw std::out_of_range("Iterator out of range");
    }

    return current_node->data;
}

template<typename Key,typename T,typename Hash>
typename HashMap<Key,T,Hash>::Iterator::pointer
HashMap<Key,T,Hash>::Iterator::operator->() const{

    if(current_node==nullptr){
        throw std::out_of_range("Iterator out of range");
    }

    return &(current_node->data);
}

template<typename Key,typename T,typename Hash>
typename HashMap<Key, T, Hash>::Iterator&
HashMap<Key, T, Hash>::Iterator::operator++(){
    advance();
    return *this;
}
        
template<typename Key,typename T,typename Hash>
typename HashMap<Key, T, Hash>::Iterator
HashMap<Key, T, Hash>::Iterator::operator++(int){

    HashMap<Key,T,Hash>::Iterator temp=*this;
    advance();
    return temp;
}

template<typename Key,typename T,typename Hash>
bool HashMap<Key, T, Hash>::Iterator::operator==(const Iterator& other) const{
    return map_==other.map_ && bucket_index==other.bucket_index && current_node== other.current_node;
}

template<typename Key,typename T,typename Hash>
bool HashMap<Key, T, Hash>::Iterator::operator!=(const Iterator& other) const{
    return !(*this==other);
}

//移动到下一个
template<typename Key,typename T,typename Hash>
void HashMap<Key, T, Hash>::Iterator::advance(){
    if(current_node!=nullptr){
        current_node=current_node->next;
    }
    while(current_node==nullptr){
        if(bucket_index+1<map_->bucket_count){
            ++bucket_index;
            current_node=map_->buckets_[bucket_index];
        }else if(bucket_index+1==map_->bucket_count){
            ++bucket_index;
            break;
        }
    }
}


//迭代器操作
template<typename Key,typename T,typename Hash>
typename HashMap<Key, T, Hash>::Iterator 
HashMap<Key, T, Hash>::begin(){
    for(size_t i=0;i<bucket_count;i++){
        if(buckets_[i]!=nullptr){

            return HashMap<Key,T,Hash>::Iterator(this,i,buckets_[i]);
        }

    }
    return end();
}

template<typename Key,typename T,typename Hash>
typename HashMap<Key, T, Hash>::Iterator 
HashMap<Key, T, Hash>::end(){
    return Iterator(this,bucket_count,nullptr);
}