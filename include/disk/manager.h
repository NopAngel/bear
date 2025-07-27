#ifndef MANAGER_H
#define MANAGER_H


#include "../colors.h"
#include "../../fs/k_printf.h"
#define MAX_FILES 100
#define MAX_CONTENT_LENGTH 1024

#define MAX_DIRECTORIES 128
#define MAX_NAME_LENGTH 12 
#define DISK_SIZE 1024 * 1024 
#define MAX_FILES 128 
#define MAX_FILENAME_LENGTH 12 


char virtual_disk[DISK_SIZE];
#define MAX_NAME_LENGTH 256
#define MAX_CONTENT_LENGTH 1024

typedef struct {
    char name[MAX_NAME_LENGTH];    
    unsigned int start_block;     
    unsigned int size;             
    char content[MAX_CONTENT_LENGTH];
} FileEntry;



typedef struct {
    char name[MAX_NAME_LENGTH];
    unsigned int parent_dir;  
    unsigned int start_block;  
    unsigned int size;           
} DirectoryEntry;
#define MAX_LINES 10000

DirectoryEntry directory_table[MAX_DIRECTORIES];
unsigned int directory_count = 0;



#define TRUE 1
#define FALSE 0
typedef int bool;


unsigned int custom_strlen(const char *str);
void clear_memory(char *buffer, unsigned int length);
void create_new_file(const char *filename, const char *content);
int fs_write(const char* filename, const char* content, unsigned int size);
int fs_read(const char* filename, char* out_buf, unsigned int max_size);
void remove_file(const char *filename);
int touch(const char *filename, const char *content);
int mkdir(const char *dirname);
int rmfile(const char *filename);


#endif