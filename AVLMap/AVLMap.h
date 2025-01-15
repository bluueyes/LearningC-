#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

template<typename Key,typename Value>
struct TreeNode{
    
    Key key;
    Value value;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(const Key& k, const Value& val):key(k),value(val),height(1),
                                            left(nullptr),right(nullptr){}


};

template<typename Key,typename Value>
requires std::totally_ordered<Key>
class AVLMap{

public:
    using TreeNodes = TreeNode<Key,Value>;

    AVLMap():root(nullptr){}

    //插入或更新键值对
    void put(const Key& key,const Value& value){

        root=insertNode(root,key,value);
    }

    //查找值，返回指向值的指针
    Value* get(const Key& key){
        
        return searchNode(root,key);
    }

    //删除键值对
    void remove(const Key& key){
        root = deleteNode(root,key);
    }

    //中序遍历，返回有序键值对
    std::vector<std::pair<Key,Value>> inorderTraversal()const{
        std::vector<std::pair<Key,Value>> res;
        inorderHelper(root,res);
        return res;
    }

    //析构函数
    ~AVLMap(){
        //使用后序遍历删除节点
        std::function<void(TreeNodes*)> destroy=[&](TreeNodes* node){
            if(node==nullptr){
                return;
            }

            destroy(node->left);
            destroy(node->right);
            delete(node);
        };

        destroy(root);
    }

private:
    TreeNodes* root;

    int getHeight(TreeNodes* node) const{
        if(node==nullptr){
            return 0;
        }
        return node->height;
    }

    int getBalance(TreeNodes* node) const{

        if(node==nullptr) return 0;

        return getHeight(node->left)-getHeight(node->right);
    }

    TreeNodes* rightRotate(TreeNodes* node){
        TreeNodes* left=node->left;
        TreeNodes* childright= left->right;

        //执行旋转
        left->right=node;
        node->left=childright;

        //返回根
        return left;
    }

    TreeNodes* leftRotate(TreeNodes* node){
        TreeNodes* right=node->right;
        TreeNodes* childleft=right->left;

        //执行旋转
        right->left=node;
        node->right=childleft;

        return right;
    }

    TreeNodes* insertNode(TreeNodes* node,const Key& key,const Value& value){

        //1.执行标准BST插入
        if(node==nullptr){
            return new TreeNodes(key,value);
        }

        if(key<node->key){
            node->left=insertNode(node->left,key,value);
        }
        else if(key>node->key){
            node->right=insertNode(node->right,key,value);
        }
        else{
            node->value=value;
            return node;
        }

        //2.更新节点高度
        node->height=1+std::max(getHeight(node->left),getHeight(node->right));

        //3.获取平衡因子
        int balance=getBalance(node);

        //左左情况
        if(balance>1 && key < node->left->key){
            return rightRotate(node);
        }
        
        //右右情况
        if(balance< -1 && key > node->right->key){
            return leftRotate(node);
        }

        //左右情况
        if(balance>1 && key > node->left->key){
            node->left=leftRotate(node->left);
            node=rightRotate(node);
        }

        //右左情况
        if(balance < -1 && key < node->right->key){
            node->right=rightRotate(node->right);
            node=leftRotate(node);
        }

        return node;
    }

    Value* searchNode(TreeNodes* node,const Key& key){
        if(node==nullptr) return nullptr;

        if(key<node->key){
            return searchNode(node->left,key);
        }
        else if(key > node->key){
            return searchNode(node->right,key);
        }
        else{
            return &(node->value);
        }


    }

    TreeNodes* getMinNode(TreeNodes* node){
        TreeNodes* current=node;
        while(current->left!=nullptr){
            current=current->left;
        }

        return current;
    }

    TreeNodes* deleteNode(TreeNodes* node,const Key& key){
        //1.执行标准的BST删除
        if(node==nullptr){
            return node;
        }

        if(key<node->key){
            node->left=deleteNode(node->left,key);
        }
        else if(key>node->key){
            node->right=deleteNode(node->right,key);
        }
        else{
            //节点有一个子节点或没有
            if((node->left==nullptr)||(node->right==nullptr)){
                TreeNodes* temp= (node->left ? node->left : node->right);

                //没有子节点
                if(temp==nullptr){
                    temp=node;
                    node=nullptr;
                }
                else{
                    *node=*temp;
                }

                delete temp;
            }
            else{
                //节点有两个子节点,获取中序后继
                TreeNodes* temp=getMinNode(node->right);

                //复制中序后继的内容到此节点
                node->key=temp->key;
                node->value=temp->value;

                //删除中序后继
                node->right=deleteNode(node->right,temp->key);
            }

        }

        //树只有一个节点
        if(node==nullptr){
            return node;
        }

        //2.更新节点高度
        node->height=1+std::max(getHeight(node->left),getHeight(node->right));

        //3.获取平衡因子
        int balance = getBalance(node);

        //4.根据平衡因子进行选择
        
        //左左情况
        if(balance>1 && getBalance(node->left)>=0)
        {
            return rightRotate(node);
        }
        
        //左右情况
        if(balance>1 && getBalance(node->left)<0){
            node->left=leftRotate(node->left);
            return rightRotate(node);

        }

        //右右情况
        if(balance<-1 && getBalance(root->right)<=0){
            return leftRotate(node);
        }

        //右左情况
        if(balance<-1 && getBalance(node->right)>0){
            node->right=rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorderHelper(TreeNodes* root,std::vector<std::pair<Key,Value>>& res) const{
        if(root==nullptr) return;
        inorderHelper(root->left,res);
        res.emplace_back(root->key,root->value);
        inorderHelper(root->right,res);
    }

};