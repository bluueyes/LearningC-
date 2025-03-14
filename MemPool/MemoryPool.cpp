 #include "MemoryPool.h"

MemoryPool::MemoryPool(size_t blockSize,size_t blockCount):_blockSize(blockSize),_blockCount(blockCount)
{
    for(int i=0;i<_blockCount;i++){
        void* data=malloc(_blockSize);
        _pool.push(data);
    }
}
MemoryPool::~MemoryPool(){
    for(int i=0;i<_blockCount;i++){
        void* data=_pool.front();
        _pool.pop();
        free(data);
    }
}

//多线程
MemoryPoolThreadSafe::MemoryPoolThreadSafe(size_t blockSize,size_t blockCount):MemoryPool(blockSize,blockCount),_b_flag(false){

}

MemoryPoolThreadSafe::~MemoryPoolThreadSafe() {

}

void* MemoryPoolThreadSafe::allocate(){

    std::unique_lock<std::mutex> lock(_mutex);
    _cond.wait(lock,[this](){
        if(_b_flag) return true;

        return !_pool.empty();
    });
    if(_b_flag) return nullptr;

    auto* data=_pool.front();
    _pool.pop();
    return data;
}

void MemoryPoolThreadSafe::deallocate(void* ptr){
    std::lock_guard<std::mutex> lock(_mutex);
    _pool.push(ptr);
}

void MemoryPoolThreadSafe::Close(){
    _b_flag=true;
    _cond.notify_all();
}

//单线程
MemoryPoolOneThread::MemoryPoolOneThread(size_t blockSize,size_t blockCount):MemoryPool(blockSize,blockCount){

}

MemoryPoolOneThread::~MemoryPoolOneThread() {

}

void* MemoryPoolOneThread::allocate(){
    if(_pool.empty()){
        throw std::bad_alloc();
    }
    auto* data=_pool.front();
    _pool.pop();
    return data;
}

void MemoryPoolOneThread::deallocate(void* ptr){

    _pool.push(ptr);
}

