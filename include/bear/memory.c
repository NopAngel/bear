#include "memory.h"

// Puntero al bloque inicial de memoria
static MemoryBlock* memory_head = (void*)0;

// Inicializa la memoria reservada
void initialize_memory(void* memory_pool, size_t size) {
    memory_head = (MemoryBlock*)memory_pool;
    memory_head->size = size - sizeof(MemoryBlock);
    memory_head->next = 0;
    memory_head->free = 1;
}

// Asigna un bloque de memoria
void* allocate_memory(size_t size) {
    MemoryBlock* current = memory_head;

    while (current != 0) {
        if (current->free && current->size >= size) {
            current->free = 0;

            // Dividir el bloque si sobra espacio
            if (current->size > size + sizeof(MemoryBlock)) {
                MemoryBlock* new_block = (MemoryBlock*)((char*)current + sizeof(MemoryBlock) + size);
                new_block->size = current->size - size - sizeof(MemoryBlock);
                new_block->next = current->next;
                new_block->free = 1;

                current->size = size;
                current->next = new_block;
            }

            return (void*)((char*)current + sizeof(MemoryBlock));
        }
        current = current->next;
    }
    return (void*)0; // Sin memoria suficiente
}

// Libera un bloque de memoria
void free_memory(void* ptr) {
    if (ptr == 0) return;

    MemoryBlock* block = (MemoryBlock*)((char*)ptr - sizeof(MemoryBlock));
    block->free = 1;

    // Combinar bloques libres adyacentes
    MemoryBlock* current = memory_head;
    while (current != 0) {
        if (current->free && current->next != 0 && current->next->free) {
            current->size += current->next->size + sizeof(MemoryBlock);
            current->next = current->next->next;
        }
        current = current->next;
    }
}
