//
// Created by secon on 2024/12/7.
//

#ifndef DAY22_MEMORY_MEMORYPOOL_H
#define DAY22_MEMORY_MEMORYPOOL_H
#include <iostream>
#include <stack>

class MemoryPool {
public:
    MemoryPool(size_t objSize, size_t totalSize);
    ~MemoryPool();
    void* allocate();
    void deallocate(void* ptr);
private:
    size_t objSize;
    size_t totalSize;
    char* pool;
    std::stack<void*> freeList;
};


#endif //DAY22_MEMORY_MEMORYPOOL_H
