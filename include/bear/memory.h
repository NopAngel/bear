#ifndef MEMORY_H
#define MEMORY_H

// Definición de tipos básicos, reemplazando las utilidades de stddef.h
typedef unsigned int size_t;

// Estructura para un bloque de memoria
typedef struct MemoryBlock {
    size_t size;                // Tamaño del bloque
    struct MemoryBlock* next;   // Puntero al siguiente bloque
    int free;                   // Indicador de si el bloque está libre
} MemoryBlock;

// Prototipos de las funciones del gestor de memoria
void initialize_memory(void* memory_pool, size_t size);
void* allocate_memory(size_t size);
void free_memory(void* ptr);

#endif
