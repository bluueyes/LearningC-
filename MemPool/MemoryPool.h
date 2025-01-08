#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

class MemoryPool{
public:
    MemoryPool(size_t blockSize,size_t blockCount);
    MemoryPool(const MemoryPool&)=delete;
    MemoryPool& operator=(const MemoryPool&)=delete;
    virtual ~MemoryPool();
    virtual void* allocate()=0;
    virtual void deallocate(void* ptr)=0;
protected:
    size_t _blockSize;
    size_t _blockCount;
    std::queue<void*> _pool;
};

class MemoryPoolThreadSafe:public MemoryPool{
public:
    MemoryPoolThreadSafe(size_t blockSize,size_t blockCount);
    
    ~MemoryPoolThreadSafe() override;
    void* allocate() override;
    void deallocate(void* ptr) override;
    void Close();
private:
    std::atomic<bool> _b_flag;
    std::mutex _mutex;
    std::condition_variable _cond;
};


class MemoryPoolOneThread:public MemoryPool{
public:
    MemoryPoolOneThread(size_t blockSize,size_t blockCount);
    ~MemoryPoolOneThread() override;
    void* allocate() override;
    void deallocate(void* ptr) override;
private:

};

