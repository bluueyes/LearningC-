#include <iostream>
#include <utility>

template<typename Key,typename T>
struct TreeNode{
    std::pair<Key,T> data;
    TreeNode* right;
    TreeNode* left;
    TreeNode* parent;

    TreeNode(const Key& key,const T& value,TreeNode* parent=nullptr):data(std::make_pair(key,value)),parent(parent)
            ,left(nullptr),right(nullptr){

    }


};


template<typename Key,typename T>
class Map{
public:
    using TreeNodes=TreeNode<Key,T>;
    Map():root(nullptr){}
    ~Map(){ clear(root); }

    //禁用拷贝和复制
    Map(const Map& )=delete;
    Map& operator=(const Map& )=delete;

    //清除
    void clear(){
        clear(root);
        root=nullptr;
    }

    //查找
    TreeNodes* find(const Key& key){
        TreeNodes* current=root;
        while(current!=nullptr){
            if(current->data.first>key){
                current=current->left;
            }else if(current->data.first<key){
                current=current->right;
            }else{
                return current;
            }
        }
        return nullptr;
    }

    //插入或更新键值
    void insert(const Key& key,const T& value){
        if(root==nullptr){
            root=new TreeNodes(key,value);
            return;
        }

        TreeNodes* current=root;
        TreeNodes* parent = nullptr;
        while(current!=nullptr){
            parent=current;
            if(key<current->data.first){
                current=current->left;
            }else if(key>current->data.first){
                current=current->right;
            }else{
                current->data.second=value;
                return;
            }
        }

        if(parent->data.first>key){
            parent->left=new TreeNodes(key,value,parent);
        }else{
            parent->right=new TreeNodes(key,value,parent);
        }
    }

    void erase(const Key& key){
        TreeNodes* node=find(key);
        if(node==nullptr) return;

        //节点有两个子节点
        if(node->left!=nullptr&&node->right!=nullptr){
            //找到中序的后继
            TreeNodes* successors=successor(node);
            node->data=successors->data; //找到大于要删除节点的最小值
            node=successors; //将node指向要删除的最小后继节点
            
        }

        //节点有一个或者没有节点
        TreeNodes* child=((node->left) ? node->left : node->right);

        if(child != nullptr){
            child->parent=node->parent;
        }

        if(node->parent==nullptr){
            root=child;
        }
        else if(node==node->parent->left){
            node->parent->left=child;
        }
        else{
            node->parent->right=child;
        }

        delete node;
    }

    T& operator[](const Key& key) {

        TreeNodes* node=find(key);
        if(node==nullptr){
            TreeNodes* parent=findKeyparent(key);
            node=new TreeNodes(key,T(),parent);
            if(parent->data.first>key){
                parent->left=node;
            }else{
                parent->right=node;
            }
        }
        return node->data.second;
    }

    class Iterator{

    public:
        using Pair=std::pair<Key,T>;
        Iterator(TreeNodes* node=nullptr):current(node){}

        Pair& operator*() {
            return current->data;
        }

        Pair* operator->() {
            return &(current->data);
        }

        //前置递增
        Iterator& operator++(){

            current=successor(current);
            return  *this;
        }

        //后置递增
        Iterator operator++(int){
            Iterator* temp=new Iterator(current);
            current=successor(current);
            return temp;
        }
        
        bool operator==(const Iterator& other){
            return other.current==current;
        }

        bool operator!=(const Iterator& other){
            return !(*this==other);
        }

        TreeNodes* minimum(TreeNodes* node) const{
            if(node==nullptr) return nullptr;
            while(node->left!=nullptr){
                node=node->left;
            }
            return node;
        }    
        
        TreeNodes* successor(TreeNodes* node){
            if(node->right!=nullptr){
                return minimum(node->right);
            }

            TreeNodes* p=node->parent;
            while(p!=nullptr && p->right==node){
                node=p;
                p=p->parent;
            }
            return p;
        }
    private:
        TreeNodes* current;
    };   

    Iterator begin() const{
        return Iterator(minimum(root));
    }

    Iterator end() const{
        return Iterator(nullptr);
    }



private:
    TreeNodes* root;
    void clear(TreeNodes* node){
        if(node==nullptr){
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    TreeNodes* minimum(TreeNodes* node) const{
        if(node==nullptr) return nullptr;
        while(node->left!=nullptr){
            node=node->left;
        }
        return node;
    }    

    TreeNodes* maxmum(TreeNodes* node) const{
        if(node==nullptr) return nullptr;
        while(node->right!=nullptr){
            node=node->right;
        }
        return node;
    }

    TreeNodes* successor(TreeNodes* node){
        // 情况 1: 如果节点有右子树，中序后继是右子树中的最小节点
        if(node->right!=nullptr){
            return minimum(node->right);
        }
    // 情况 2: 如果节点没有右子树，向上找直到找到一个是父节点的左子节点的父节点
        TreeNodes* p=node->parent;
        while(p!=nullptr&&p->right==node){
            node=p;
            p=p->parent;
        }
        return p;
    }

    TreeNodes* predecessor(TreeNodes* node) const{
        if(node->left!=nullptr){
            return maxmum(node->left);
        }

        TreeNodes* p=node->parent;
        while(p->left==node && p!=nullptr){
            node=p;
            p=p->parent;
        }
        return p;
    }

    TreeNodes* findKeyparent(const Key& key){
        TreeNodes* current=root;
        TreeNodes* parent=nullptr;
        while(current!=nullptr){
            parent=current;
            if(current->data.first>key){
                current=current->left;
            }else if(current->data.first<key){
                current=current->right;
            }else{
                return current->parent;
            }
        }
        return parent;
    }

};