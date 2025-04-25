#include "ext4_fs.h"

void initialize_ext4(struct superblock *sb, struct inode *inodes) {
    sb->total_blocks = 10000;
    sb->free_blocks = 10000;
    sb->total_inodes = MAX_INODES;
    sb->free_inodes = MAX_INODES;
    sb->block_size = BLOCK_SIZE;

    for (uint32_t i = 0; i < MAX_INODES; i++) {
        inodes[i].inode_number = i;
        inodes[i].file_size = 0;
        for (uint32_t j = 0; j < 12; j++) {
            inodes[i].block_pointers[j] = 0;
        }
    }
}

struct inode *create_inode(struct superblock *sb, struct inode *inodes, uint32_t size) {
    if (sb->free_inodes == 0 || sb->free_blocks < size / BLOCK_SIZE + (size % BLOCK_SIZE != 0)) {
        return (struct inode *)0;
    }

    struct inode *new_inode = (struct inode *)0;

    for (uint32_t i = 0; i < MAX_INODES; i++) {
        if (inodes[i].file_size == 0) {
            new_inode = &inodes[i];
            new_inode->file_size = size;
            sb->free_inodes--;
            sb->free_blocks -= size / BLOCK_SIZE + (size % BLOCK_SIZE != 0);
            break;
        }
    }

    return new_inode;
}

void delete_inode(struct superblock *sb, struct inode *inodes, uint32_t inode_number) {
    if (inode_number >= MAX_INODES || inodes[inode_number].file_size == 0) {
        return;
    }

    sb->free_inodes++;
    sb->free_blocks += inodes[inode_number].file_size / BLOCK_SIZE + (inodes[inode_number].file_size % BLOCK_SIZE != 0);
    inodes[inode_number].file_size = 0;

    for (uint32_t j = 0; j < 12; j++) {
        inodes[inode_number].block_pointers[j] = 0;
    }
}

struct inode *create_file(struct superblock *sb, struct inode *inodes, uint32_t file_size, uint32_t *data_blocks) {
    if (sb->free_inodes == 0 || sb->free_blocks < file_size / BLOCK_SIZE + (file_size % BLOCK_SIZE != 0)) {
        return (struct inode *)0;
    }

    struct inode *new_inode = (struct inode *)0;

    for (uint32_t i = 0; i < MAX_INODES; i++) {
        if (inodes[i].file_size == 0) {
            new_inode = &inodes[i];
            new_inode->file_size = file_size;
            sb->free_inodes--;
            sb->free_blocks -= file_size / BLOCK_SIZE + (file_size % BLOCK_SIZE != 0);

            for (uint32_t j = 0; j < 12 && file_size > 0; j++) {
                new_inode->block_pointers[j] = *data_blocks;
                data_blocks++;
                file_size -= BLOCK_SIZE;
            }
            break;
        }
    }

    return new_inode;
}
