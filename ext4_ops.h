#ifndef EXT4_OPS_H
#define EXT4_OPS_H

#define MAX_PATH_LENGTH 256
#define MAX_DIRECTORY_ENTRIES 1024

typedef unsigned int uint32_t;

struct directory {
    uint32_t inode_number;
    char name[MAX_PATH_LENGTH];
    struct directory *parent;
    struct directory *entries[MAX_DIRECTORY_ENTRIES];
};

int mkdir(struct directory *current, char *name, unsigned int inode_number);

void rmdir(struct directory *current, char *name);
void cd(struct directory **current, char *name);
void rm(struct directory *current, char *name);
unsigned int vga_display(char *message, unsigned int line, unsigned int color);
int ls(struct directory *current);



#endif
