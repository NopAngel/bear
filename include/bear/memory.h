#ifndef MEMORY_H
#define MEMORY_H


#include "../../fs/k_printf.h"

typedef unsigned int size_t;

typedef struct MemoryBlock {
    size_t size;                // size block
    struct MemoryBlock* next;   // pointer block
    int free;                  
} MemoryBlock;

void initialize_memory(void* memory_pool, size_t size);
void* allocate_memory(size_t size);
void free_memory(void* ptr);

#endif
