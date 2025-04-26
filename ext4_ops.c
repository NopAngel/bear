#include "ext4_ops.h"

struct directory preallocated_directories[MAX_DIRECTORY_ENTRIES];
uint32_t directory_allocation_map[MAX_DIRECTORY_ENTRIES];

void initialize_allocation_map() {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        directory_allocation_map[i] = 0; 
    }
}

struct directory *allocate_directory() {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (directory_allocation_map[i] == 0) {
            directory_allocation_map[i] = 1; 
            return &preallocated_directories[i];
        }
    }
    return (struct directory *)0; 
}

void free_directory(struct directory *dir) {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (&preallocated_directories[i] == dir) {
            directory_allocation_map[i] = 0; 
            return;
        }
    }
}
void mkdir(struct directory *current, char *name, uint32_t inode_number) {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (current->entries[i] == (struct directory *)0) { 
            struct directory *new_dir = allocate_directory();
            if (new_dir == (struct directory *)0) {
                return; 
            }

            
            new_dir->inode_number = inode_number;
            uint32_t j = 0;
            while (name[j] != '\0' && j < MAX_PATH_LENGTH - 1) {
                new_dir->name[j] = name[j];
                j++;
            }
            new_dir->name[j] = '\0'; 
            new_dir->parent = current;

            for (uint32_t k = 0; k < MAX_DIRECTORY_ENTRIES; k++) {
                new_dir->entries[k] = (struct directory *)0;
            }

   
            current->entries[i] = new_dir;
            return; 
        }
    }
}



void rmdir(struct directory *current, char *name) {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (current->entries[i] != (struct directory *)0) {
            uint32_t match = 1;
            for (uint32_t j = 0; j < MAX_PATH_LENGTH; j++) {
                if (current->entries[i]->name[j] != name[j]) {
                    match = 0;
                    break;
                }
                if (name[j] == '\0') break;
            }
            if (match) {
                free_directory(current->entries[i]);
                current->entries[i] = (struct directory *)0;
                break;
            }
        }
    }
}

void cd(struct directory **current, char *name) {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if ((*current)->entries[i] != (struct directory *)0) {
            uint32_t match = 1;
            for (uint32_t j = 0; j < MAX_PATH_LENGTH; j++) {
                if ((*current)->entries[i]->name[j] != name[j]) {
                    match = 0;
                    break;
                }
                if (name[j] == '\0') break;
            }
            if (match) {
                *current = (*current)->entries[i];
                break;
            }
        }
    }
}

void rm(struct directory *current, char *name) {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (current->entries[i] != (struct directory *)0) {
            uint32_t match = 1;
            for (uint32_t j = 0; j < MAX_PATH_LENGTH; j++) {
                if (current->entries[i]->name[j] != name[j]) {
                    match = 0;
                    break;
                }
                if (name[j] == '\0') break;
            }
            if (match) {
                free_directory(current->entries[i]);
                current->entries[i] = (struct directory *)0;
                break;
            }
        }
    }
}


unsigned int vga_display(char *message, unsigned int line, unsigned int color)
{
    char *vidmem = (char *) 0xb8000;
    unsigned int i = 0;

    i = (line * 80 * 2);

    while (*message != 0)
    {
        if (*message == '\n') // check the new line
        {
            line++;
            i = (line * 80 * 2);
            *message++;
        }
        else
        {
            vidmem[i] = *message;
            *message++;
            i++;
            vidmem[i] = color;
            i++;
        }
    }

    return (1);
}

void ls(struct directory *current) {
    unsigned int line = 0; // Línea inicial para impresión
    unsigned int color = 0x07; // Color blanco sobre negro

    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (current->entries[i] != (struct directory *)0) { // Si hay una entrada válida
            vga_display(current->entries[i]->name, line, color); // Muestra el nombre del directorio
            line++; // Mueve a la siguiente línea
        }
    }
}
