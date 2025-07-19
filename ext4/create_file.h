#ifndef CREATE_FILE_H
#define CREATE_FILE_H

struct inode *create_file(struct superblock *sb, struct inode *inodes, uint32_t file_size, uint32_t *data_blocks);


#endif