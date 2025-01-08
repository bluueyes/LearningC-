#include "MemoryPool.h"
class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "MyClass constructor: " << value << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructor: " << value << std::endl;
    }
    int value;
};

int main() {
    try {
        // 创建一个能容纳 3 个 MyClass 对象的内存池
        MemoryPool* pool=new MemoryPoolOneThread(sizeof(MyClass), 3);

        // 分配对象内存
        void* mem1 = pool->allocate();
        void* mem2 = pool->allocate();

        // 使用“定位 new”构造对象
        MyClass* obj1 = new(mem1) MyClass(100);
        MyClass* obj2 = new(mem2) MyClass(200);

        // 使用对象
        std::cout << "obj1 value: " << obj1->value << std::endl;
        std::cout << "obj2 value: " << obj2->value << std::endl;

        // 显式调用析构函数
        obj1->~MyClass();
        obj2->~MyClass();

        // 释放内存
        pool->deallocate(mem1);
        pool->deallocate(mem2);

    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory pool allocation error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}