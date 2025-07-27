#include "nvmem.h"

// Direct hardware access functions
static inline void ata_write_sector(unsigned int lba, unsigned char *buffer) {
    // Implement your actual ATA write function here
    // This is just a placeholder that matches your ATA driver's implementation
    unsigned short *buf = (unsigned short *)buffer;
    for (int i = 0; i < 256; i++) {
        unsigned short port = 0x1F0;
        unsigned short data = buf[i];
        asm volatile("outw %0, %1" : : "a"(data), "Nd"(port));
    }
}

static inline void ata_read_sector(unsigned int lba, unsigned char *buffer) {
    // Implement your actual ATA read function here
    // This is just a placeholder that matches your ATA driver's implementation
    unsigned short *buf = (unsigned short *)buffer;
    for (int i = 0; i < 256; i++) {
        unsigned short port = 0x1F0;
        unsigned short data;
        asm volatile("inw %1, %0" : "=a"(data) : "Nd"(port));
        buf[i] = data;
    }
}

static unsigned int nvmem_initialized = 0;

void nvmem_init() {
    unsigned char test_buffer[NVMEM_SECTOR_SIZE];
    if (nvmem_initialized) return;
    ata_read_sector(0, test_buffer);
    nvmem_initialized = 1;
}

int nvmem_read(unsigned int sector, unsigned char *buffer) {
    if (!nvmem_initialized || sector >= NVMEM_MAX_SECTORS) return -1;
    ata_read_sector(sector, buffer);
    return 0;
}

int nvmem_write(unsigned int sector, unsigned char *buffer) {
    unsigned char verify_buffer[NVMEM_SECTOR_SIZE];
    if (!nvmem_initialized || sector >= NVMEM_MAX_SECTORS) return -1;
    
    ata_write_sector(sector, buffer);
    ata_read_sector(sector, verify_buffer);
    
    for (int i = 0; i < NVMEM_SECTOR_SIZE; i++) {
        if (buffer[i] != verify_buffer[i]) return -2;
    }
    return 0;
}

/*

how to use:

#include "nvmem.h"

void save_config() {
    unsigned char config_data[NVMEM_SECTOR_SIZE] = {0};
    // Fill config_data...
    nvmem_write(1, config_data);  // Save to sector 1
}

void load_config() {
    unsigned char config_data[NVMEM_SECTOR_SIZE];
    if (nvmem_read(1, config_data) == 0) {
        // Use config_data...
    }
}

*/