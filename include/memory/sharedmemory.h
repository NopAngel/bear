#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#define SHARED_MEMORY_SIZE 4096
#define MAX_SHARED_BLOCKS 8     

typedef struct {
    int is_used;             
    void *start_address;      
    unsigned int size;  
} shared_block_t;

extern shared_block_t shared_blocks[MAX_SHARED_BLOCKS];
extern void *shared_memory_base;

void init_shared_memory();
void *allocate_shared_memory(unsigned int size);
void free_shared_memory(void *address);

#endif
