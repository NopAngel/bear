#include "fs_driver.h"
#include "bear/k_printf.h" // Para usar k_printf

static FileSystem fs;

// Inicializa el sistema de archivos
void fs_init() {
    for (uint32_t i = 0; i < MAX_FILES; i++) {
        fs.files[i].name[0] = '\0';  // Marca como vacío
        fs.files[i].size = 0;
        fs.files[i].start_block = 0;
        fs.allocation_table[i] = 0; // No asignado
    }
    k_printf("Sistema de archivos inicializado.\n", 10, 0x0F); // Línea 10
}

// Crea un archivo
uint8_t fs_create_file(const char* name, uint32_t size) {
    for (uint32_t i = 0; i < MAX_FILES; i++) {
        if (fs.files[i].name[0] == '\0') {  // Encuentra un espacio libre
            for (uint32_t j = 0; j < MAX_FILES; j++) {
                if (fs.allocation_table[j] == 0) { // Encuentra un bloque libre
                    fs.files[i].start_block = j;
                    fs.files[i].size = size;
                    fs.allocation_table[j] = 1; // Marca el bloque como ocupado
                    for (uint32_t k = 0; k < MAX_FILENAME_LEN - 1 && name[k] != '\0'; k++) {
                        fs.files[i].name[k] = name[k];
                    }
                    fs.files[i].name[MAX_FILENAME_LEN - 1] = '\0';
                    k_printf("Archivo creado: %s\n", 11, 0x0A); // Línea 11, color verde
                    return 1; // Éxito
                }
            }
        }
    }
    k_printf("Error: No se puede crear el archivo. Sistema lleno.\n", 12, 0x04); // Línea 12
    return 0; // Error
}

// Lee datos de un archivo
uint8_t fs_read_file(const char* name, uint8_t* buffer, uint32_t size, uint32_t offset) {
    for (uint32_t i = 0; i < MAX_FILES; i++) {
        if (fs.files[i].name[0] != '\0' && strcmp(fs.files[i].name, name) == 0) {
            if (offset + size > fs.files[i].size) {
                size = fs.files[i].size - offset; // Ajusta si se excede el tamaño
            }
            for (uint32_t j = 0; j < size; j++) {
                buffer[j] = 0xAB; // Dato simulado
            }
            k_printf("Archivo %s leído (%d bytes).\n", 13, 0x0F); // Línea 13
            return 1; // Éxito
        }
    }
    k_printf("Error: Archivo %s no encontrado.\n", 14, 0x04); // Línea 14
    return 0; // Error
}

// Escribe datos en un archivo
uint8_t fs_write_file(const char* name, const uint8_t* data, uint32_t size, uint32_t offset) {
    for (uint32_t i = 0; i < MAX_FILES; i++) {
        if (fs.files[i].name[0] != '\0' && strcmp(fs.files[i].name, name) == 0) {
            if (offset + size > fs.files[i].size) {
                k_printf("Error: Escribir fuera del rango.\n", 15, 0x04); // Línea 15
                return 0; // Error
            }
            k_printf("Archivo %s escrito (%d bytes).\n", 16, 0x0A); // Línea 16
            return 1; // Éxito
        }
    }
    k_printf("Error: Archivo %s no encontrado.\n", 17, 0x04); // Línea 17
    return 0; // Error
}

// Lista los archivos
void fs_list_files() {
    k_printf("Archivos en el sistema:\n", 18, 0x07); // Línea 18
    for (uint