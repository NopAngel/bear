#include "manager.h"


FileEntry file_table[MAX_FILES];  
unsigned int file_count = 0;



#define TRUE 1
#define FALSE 0
typedef int bool;

unsigned int custom_strlen(const char *str) {
    unsigned int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

unsigned int cursor_y = 0;



void clear_memory(char *buffer, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        buffer[i] = 0;  
    }
}


FileEntry file_table[MAX_FILES];  


#define MAX_CONTENT_LENGTH 1024



char content[MAX_CONTENT_LENGTH];

char virtual_disk[DISK_SIZE];





typedef struct {
    char name[MAX_NAME_LENGTH];
    unsigned int parent_dir;  
    unsigned int start_block;  
    unsigned int size;           
} DirectoryEntry;
#define MAX_LINES 10000

DirectoryEntry directory_table[MAX_DIRECTORIES];
unsigned int directory_count = 0;

void create_new_file(const char *filename, const char *content) {
    custom_strcpy(file_table[file_count].name, filename);   
    custom_strcpy(file_table[file_count].content, content); 
    file_table[file_count].size = custom_strlen(content);   
    file_table[file_count].start_block = directory_count * 16 + file_count;
    file_count++;
}

int fs_write(const char* filename, const char* content, unsigned int size) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) {
            custom_strcpy(file_table[i].content, content);
            file_table[i].size = size;
            return 0;
        }
    }

    if (file_count >= MAX_FILES) return -1;

    custom_strcpy(file_table[file_count].name, filename);
    custom_strcpy(file_table[file_count].content, content);
    file_table[file_count].size = size;
    file_table[file_count].start_block = directory_count * 16 + file_count;
    file_count++;
    return 0;
}


int fs_read(const char* filename, char* out_buf, unsigned int max_size) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) {
            if (file_table[i].size > max_size) return -2;

            custom_strcpy(out_buf, file_table[i].content);
            return file_table[i].size;
        }
    }
    return -1; 
}




void remove_file(const char *filename) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) {
            for (unsigned int j = i; j < file_count - 1; j++) {
                file_table[j] = file_table[j + 1];  
            }
            file_count--; 
            return;
        }
    }
}



int touch(const char *filename, const char *content) {
    create_new_file(filename, content);
    return 0;
}


int mkdir(const char *dirname) {

    if (directory_count >= MAX_DIRECTORIES) {
        k_printf("Error: No more directories can be created", 0, RED_TXT);
        return -1;
    }


    if (strlen(dirname) >= MAX_NAME_LENGTH) {
        k_printf("Error: The name is long.", 0, RED_TXT);
        return -1;
    }

    for (unsigned int i = 0; i < directory_count; i++) {
        if (strcmp(directory_table[i].name, dirname) == 0) {
            k_printf("Error: The directory already exists.", 0, RED_TXT);
            return -1;
        }
    }

 
    strcpy(directory_table[directory_count].name, dirname); 
    directory_table[directory_count].start_block = directory_count * 16; 
    directory_table[directory_count].size = 1; 
    directory_count++; 

    k_printf("Directory's created.", cursor_y++, GREEN_TXT);
    return 0;
}



int rmfile(const char *filename) {
	remove_file(filename);
	return 0;
}


