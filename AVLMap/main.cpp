#include "AVLMap.h"


// 示例主函数
int main() {
    // 示例 1：int 键，std::string 值
    std::cout << "示例 1：int 键，std::string 值\n";
    AVLMap<int, std::string> avlMap1;

    // 插入键值对
    avlMap1.put(10, "十");
    avlMap1.put(20, "二十");
    avlMap1.put(30, "三十");
    avlMap1.put(40, "四十");
    avlMap1.put(50, "五十");
    avlMap1.put(25, "二十五");

    // 中序遍历
    std::vector<std::pair<int, std::string>> traversal1 = avlMap1.inorderTraversal();
    std::cout << "中序遍历: ";
    for (const auto& pair : traversal1) {
        std::cout << "(" << pair.first << ", \"" << pair.second << "\") ";
    }
    std::cout << std::endl;

    //查找键
    std::string* val1 = avlMap1.get(20);
    if (val1)
        std::cout << "获取键20的值: " << *val1 << std::endl;
    else
        std::cout << "键20不存在。" << std::endl;

    val1 = avlMap1.get(25);
    if (val1)
        std::cout << "获取键25的值: " << *val1 << std::endl;
    else
        std::cout << "键25不存在。" << std::endl;

    val1 = avlMap1.get(60);
    if (val1)
        std::cout << "获取键60的值: " << *val1 << std::endl;
    else
        std::cout << "键60不存在。" << std::endl;

    // 删除键20
    avlMap1.remove(20);
    std::cout << "删除键20后，中序遍历: ";
    traversal1 = avlMap1.inorderTraversal();
    for (const auto& pair : traversal1) {
        std::cout << "(" << pair.first << ", \"" << pair.second << "\") ";
    }
    std::cout << std::endl;

    std::cout << "\n-----------------------------\n";

    // 示例 2：std::string 键，double 值
    std::cout << "示例 2：std::string 键，double 值\n";
    AVLMap<std::string, double> avlMap2;

    // 插入键值对
    avlMap2.put("apple", 1.99);
    avlMap2.put("banana", 0.99);
    avlMap2.put("cherry", 2.99);
    avlMap2.put("date", 3.49);
    avlMap2.put("elderberry", 5.99);
    avlMap2.put("fig", 2.49);

    // 中序遍历
    std::vector<std::pair<std::string, double>> traversal2 = avlMap2.inorderTraversal();
    std::cout << "中序遍历: ";
    for (const auto& pair : traversal2) {
        std::cout << "(\"" << pair.first << "\", " << pair.second << ") ";
    }
    std::cout << std::endl;

    // 查找键
    double* val2 = avlMap2.get("banana");
    if (val2)
        std::cout << "获取键\"banana\"的值: " << *val2 << std::endl;
    else
        std::cout << "键\"banana\"不存在。" << std::endl;

    val2 = avlMap2.get("fig");
    if (val2)
        std::cout << "获取键\"fig\"的值: " << *val2 << std::endl;
    else
        std::cout << "键\"fig\"不存在。" << std::endl;

    val2 = avlMap2.get("grape");
    if (val2)
        std::cout << "获取键\"grape\"的值: " << *val2 << std::endl;
    else
        std::cout << "键\"grape\"不存在。" << std::endl;

    // 删除键"banana"
    avlMap2.remove("banana");
    std::cout << "删除键\"banana\"后，中序遍历: ";
    traversal2 = avlMap2.inorderTraversal();
    for (const auto& pair : traversal2) {
        std::cout << "(\"" << pair.first << "\", " << pair.second << ") ";
    }
    std::cout << std::endl;

    return 0;
}