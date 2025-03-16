/*
 * BearOS - File System Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef FS_DRIVER_H
#define FS_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Tamaños básicos
#define FS_BLOCK_SIZE 512      // Tamaño de bloque
#define MAX_FILENAME_LEN 32    // Longitud máxima de nombre de archivo
#define MAX_FILES 128          // Número máximo de archivos

// Estructura de un archivo
typedef struct {
    char name[MAX_FILENAME_LEN]; // Nombre del archivo
    uint32_t size;               // Tamaño del archivo en bytes
    uint32_t start_block;        // Bloque inicial del archivo
} FileEntry;

// Estructura del sistema de archivos (tabla de archivos)
typedef struct {
    FileEntry files[MAX_FILES];  // Lista de archivos
    uint8_t allocation_table[MAX_FILES]; // Tabla de asignación simple
} FileSystem;

// Inicializa el sistema de archivos
void fs_init();

// Crea un archivo
uint8_t fs_create_file(const char* name, uint32_t size);

// Lee datos de un archivo
uint8_t fs_read_file(const char* name, uint8_t* buffer, uint32_t size, uint32_t offset);

// Escribe datos en un archivo
uint8_t fs_write_file(const char* name, const uint8_t* data, uint32_t size, uint32_t offset);

// Lista los archivos en el sistema de archivos
void fs_list_files();

#endif // FS_DRIVER_H
