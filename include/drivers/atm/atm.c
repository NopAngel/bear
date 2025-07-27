#include "atm.h"


typedef unsigned char uint8_t;
#define NULL ((void*)0)    
static uint8_t memory_pool[1024 * 1024]; // 1MB heap
static size_t next_free = 0;

void *atm_alloc(size_t size) {
    if (next_free + size > sizeof(memory_pool)) return NULL;
    void *ptr = &memory_pool[next_free];
    next_free += size;
    return ptr;
}

void atm_free(void *ptr) {
    // (this is example :)
}