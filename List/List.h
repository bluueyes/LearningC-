#include <iostream>

template<typename T>
struct Node{
    T data;
    Node* next;
    Node* prev;
    Node(const T& data=T()):data(data),next(nullptr),prev(nullptr){}
};

template<typename T>
class List;

template<typename T>
class Iterator{
public:
    using value_type=T;
    using reference=T&;
    using pointer=T*;
    using difference_type=std::ptrdiff_t;
    using iterator_category=std::bidirectional_iterator_tag;
    using self_type=Iterator<T>;

    Iterator(Node<T>* node):_node(node){}

    reference operator*(){
        return _node->data;
    }

    pointer operator->(){
        return &_node->data;
    }

    self_type& operator++(){
       if(_node) _node=_node->next;
        return *this;
    }

    self_type operator++(int){
        self_type temp=*this;
        *this++;
        return temp;
    }

    self_type& operator--(){
        if(_node) _node=_node->prev;
        return *this;
    }

    self_type operator--(int){
        self_type temp=*this;
        *this--;
        return temp;
    }

    bool operator==(const self_type& other){
        return _node==other.node;
    }

    bool operator!=(const self_type& other){
        return !(*this==other);
    }

private:
    Node<T>* _node;
    friend class List<T>;
};


template<typename T>
class List{
public:
    List(){
        _head=new Node<T>();
        _tail=new Node<T>();
        _head->next=_tail;
        _tail->prev=_head;
    }
    void clear(){
        Node<T>* node=_head->next;
        while(node!=_tail){
            Node<T>* next=node->next;
            delete node;
            node=next;
        }
        _head->next=_tail;
        _tail->prev=_head;
    }

    ~List(){
        clear();
        delete _head;
        delete _tail;
    }
    // 禁止拷贝构造和赋值操作（简化实现）
    List(const List& other) = delete;
    List& operator=(const List& other) = delete;

    void push_back(const T& data){
        Node<T>* node=new Node<T>(data);
        Node<T>* prev=_tail->prev;
        prev->next=node;
        node->prev=prev;
        node->next=_tail;
        _tail->prev=node;    
    }

    void push_front(const T& data){
        Node<T>* node=new Node<T>(data);
        Node<T>* next=_head->next;
        _head->next=node;
        node->prev=_head;
        next->prev=node;
        node->next=next;
    }

    bool empty() const{
        return _head->next==_tail;
    }

    void pop_back(){
        if(empty()) return;
        Node<T>* node=_tail->prev;
        Node<T>* prev=node->prev;
        prev->next=_tail;
        _tail->prev=prev;
        delete node;
    }

    void pop_front(){
        if(empty()) return;
        Node<T>* node=_head->next;
        Node<T>* next=node->next;
        _head->next=next;
        next->prev=_head;
        delete node;
    }

    Iterator<T> begin(){
        return Iterator<T>(_head->next);
    }

    Iterator<T> end(){
        return Iterator<T>(_tail);
    }

    Iterator<T> rbegin(){
        return Iterator<T>(_tail->prev);
    }

    Iterator<T> rend(){
        return Iterator<T>(_head);
    }

    Iterator<T> insert(Iterator<T> pos,const T& data){
        Node<T>* node = new Node<T>(data);
        Node<T>* current=pos._node;
        Node<T>* prev=current->prev;
        prev->next=node;
        node->prev=prev;
        node->next=current;
        current->prev=node;

        
        return Iterator<T>(node);
    }

    Iterator<T> erase(Iterator<T> pos){
        Node<T>* current=pos._node;
        if(current==_head||current==_tail) return pos;

        Node<T>* prev=current->prev;
        Node<T>* next=current->next;
        
        prev->next=next;
        next->prev=prev;
        delete current;
    
        return Iterator<T>(next);
    }

    Iterator<T> erase(Iterator<T> first,Iterator<T> last){
        Node<T>* begin=first._node;
        Node<T>* end=last._ndoe;
        while(begin!=end){
            Node<T>* temp=begin;
            begin=begin->next;
            erase(Iterator<T>(temp));
        }
    }

    void reverse(){
        Node<T>* current=_head;
        while(current){
            Node<T>* temp=current->next;
            current->next=current->prev;
            current->prev=temp;
            current=temp;
        }
        Node<T>* temp=_head;
        _head=_tail;
        _tail=temp; 
    }

    void print(){
        Node<T>* current=_head->next;
        while(current!=_tail)
        {
            std::cout<<current->data<<" ";
            current=current->next;
        }
        std::cout<<std::endl;
    }
    
    void remove(const T& data){
        Iterator<T> it=begin();
        while(it!=end()){
            if(*it==data){
                it=erase(it);
            }else{
                ++it;
            }
        }
    }

private:
    Node<T>* _head;
    Node<T>* _tail;
    
};