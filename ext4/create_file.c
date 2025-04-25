struct inode *create_file(struct superblock *sb, struct inode *inodes, uint32_t file_size, uint32_t *data_blocks) {
    if (sb->free_inodes == 0 || sb->free_blocks < file_size / BLOCK_SIZE + (file_size % BLOCK_SIZE != 0)) {
        return (struct inode *)0; // No hay espacio suficiente
    }

    struct inode *new_inode = (struct inode *)0;

    for (uint32_t i = 0; i < MAX_INODES; i++) {
        if (inodes[i].file_size == 0) {
            new_inode = &inodes[i];
            new_inode->file_size = file_size;
            sb->free_inodes--;
            
            for (uint32_t j = 0; j < 12 && file_size > 0; j++) {
                new_inode->block_pointers[j] = *data_blocks;
                data_blocks++;
                file_size -= BLOCK_SIZE;
                sb->free_blocks--;
            }
            break;
        }
    }

    return new_inode; 
}
