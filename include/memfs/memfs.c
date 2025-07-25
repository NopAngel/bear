int memfs_open(const char *path, int flags) {
    if (path[0] == '/' && path[1] == 'm' && path[2] == 'n')
        return 0; 
    return -1;
}

int memfs_close(int fd) {
    return 0;
}



int memfs_read(int fd, void *buf, unsigned int count) {
    const char *fake = "from memfs.";
    unsigned int i;
    for (i = 0; i < count && fake[i]; i++)
        ((char*)buf)[i] = fake[i];
    return i;
}

int memfs_write(int fd, const void *buf, unsigned int count) {
    return count; 
}
