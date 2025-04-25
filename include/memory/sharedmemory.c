

/*
*
*   sharedmemory.c - shared memory (optimization)
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/


void *allocate_shared_memory(unsigned int size);
void free_shared_memory(void *address);
void init_shared_memory();


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



/*

CANT' use:


void kernel_main() {
    // Inicializar la memoria compartida
    init_shared_memory();

    // Proceso 1 solicita un bloque
    void *block1 = allocate_shared_memory(512);
    if (block1) {
        k_printf("Proceso 1 reservó memoria en: 0x%x\n", (unsigned int)block1);
    }

    // Proceso 2 solicita otro bloque
    void *block2 = allocate_shared_memory(1024);
    if (block2) {
        k_printf("Proceso 2 reservó memoria en: 0x%x\n", (unsigned int)block2);
    }

    // Proceso 1 libera su bloque
    free_shared_memory(block1);
    k_printf("Proceso 1 liberó su bloque\n");

    // Proceso 3 solicita un nuevo bloque
    void *block3 = allocate_shared_memory(512);
    if (block3) {
        k_printf("Proceso 3 reservó memoria en: 0x%x\n", (unsigned int)block3);
    }

    while (1); // Mantener el kernel en ejecución
}*/