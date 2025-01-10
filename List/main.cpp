#include <iostream>
#include "List.h"

// 测试代码
int main() {
    List<int> lst;
    
    // 插入元素
    lst.push_back(10);    // 链表: 10
    lst.push_front(5);    // 链表: 5, 10
    lst.push_back(15);    // 链表: 5, 10, 15
    lst.insert(++lst.begin(), 7); // 链表: 5, 7, 10, 15

    // 打印链表
    std::cout << "链表内容: ";
    lst.print(); // 输出: 5 7 10 15

    // 删除元素
    lst.pop_front(); // 链表: 7, 10, 15
    lst.pop_back();  // 链表: 7, 10

    // 打印链表
    std::cout << "删除头尾后链表内容: ";
    lst.print(); // 输出: 7 10

    // 插入和删除
    auto it = lst.begin();
    it=lst.insert(it, 3);  // 链表: 3, 7, 10

    std::cout<<"insert 之后内容为: ";
    lst.print();
    lst.erase(++it);    // 链表: 3, 10

    // 打印链表
    std::cout << "插入和删除后链表内容: ";
    lst.print(); // 输出: 3 10

    // 清空链表
    lst.clear();
    std::cout << "清空后，链表是否为空: " << (lst.empty() ? "是" : "否") << std::endl;

    return 0;
}