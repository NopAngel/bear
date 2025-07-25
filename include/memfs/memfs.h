#ifndef MEMFS_H
#define MEMFS_H

int memfs_open(const char *path, int flags);
int memfs_close(int fd);
int memfs_read(int fd, void *buf, unsigned int count);
int memfs_write(int fd, const void *buf, unsigned int count);

#endif // MEMFS_H