#ifndef EXT4_FS_H
#define EXT4_FS_H

#define BLOCK_SIZE 4096
#define MAX_INODES 1024

typedef unsigned int uint32_t;

struct superblock {
    uint32_t total_blocks;
    uint32_t free_blocks;
    uint32_t total_inodes;
    uint32_t free_inodes;
    uint32_t block_size;
};

struct inode {
    uint32_t inode_number;
    uint32_t file_size;
    uint32_t block_pointers[12];
};

void initialize_ext4(struct superblock *sb, struct inode *inodes);
struct inode *create_inode(struct superblock *sb, struct inode *inodes, uint32_t size);
void delete_inode(struct superblock *sb, struct inode *inodes, uint32_t inode_number);
struct inode *create_file(struct superblock *sb, struct inode *inodes, uint32_t file_size, uint32_t *data_blocks);

#endif
