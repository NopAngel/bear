#ifndef _NVMEM_DRIVER_H
#define _NVMEM_DRIVER_H

#define NVMEM_SECTOR_SIZE 512
#define NVMEM_MAX_SECTORS 1024

void nvmem_init();
int nvmem_read(unsigned int sector, unsigned char *buffer);
int nvmem_write(unsigned int sector, unsigned char *buffer);

#endif