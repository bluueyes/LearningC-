#include "Map.h"

int main() {
    Map<std::string, int> myMap;

    // 插入元素
    myMap.insert("apple", 3);
    myMap.insert("banana", 5);
    myMap.insert("orange", 2);
    myMap.insert("grape", 7);
    myMap.insert("cherry", 4);

    // 使用迭代器遍历元素（按键的字母顺序）
    std::cout << "Map contents (in-order):\n";
    for(auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    // 查找元素
    std::string keyToFind = "banana";
    auto node = myMap.find(keyToFind);
    if(node != nullptr) {
        std::cout << "\nFound " << keyToFind << " with value: " << node->data.second << "\n";
    } else {
        std::cout << "\n" << keyToFind << " not found.\n";
    }

    // 删除元素
    myMap.erase("apple");
    myMap.erase("cherry");


    // 再次遍历
    std::cout << "\nAfter erasing apple and cherry:\n";
    for(auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    myMap["apple"]=4;
    myMap["cherry"]=11;

    //myMap.insert("apple1",11);
    //myMap.insert("cherry1",11);
    
    // 再次遍历
    std::cout << "\nAfter operator[] apple and cherry:\n";
    for(auto it=myMap.begin();it!=myMap.end();++it){
        std::cout<<it->first<<" => "<<it->second<<"\n";
    }

    return 0;
}