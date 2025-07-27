
#define SHARED_MEMORY_SIZE 4096
#define MAX_SHARED_BLOCKS 8     

typedef struct {
    int is_used;             
    void *start_address;      
    unsigned int size;  
} shared_block_t;

shared_block_t shared_blocks[MAX_SHARED_BLOCKS];
void *shared_memory_base = (void *)0x100000;


void init_shared_memory() {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        shared_blocks[i].is_used = 0;
        shared_blocks[i].start_address = shared_memory_base + (i * (SHARED_MEMORY_SIZE / MAX_SHARED_BLOCKS));
        shared_blocks[i].size = SHARED_MEMORY_SIZE / MAX_SHARED_BLOCKS;
    }
}


void *allocate_shared_memory(unsigned int size) {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        if (!shared_blocks[i].is_used && shared_blocks[i].size >= size) {
            shared_blocks[i].is_used = 1; 
            return shared_blocks[i].start_address;
        }
    }
    return 0; 
}

void free_shared_memory(void *address) {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        if (shared_blocks[i].start_address == address) {
            shared_blocks[i].is_used = 0;
            return;
        }
    }
}


void clear_memory(char *buffer, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        buffer[i] = 0;  
    }
}
