#include "ata.h"

static void ata_wait() {
    unsigned char status;
    do {
        __asm__ volatile(
            "inb %%dx, %%al"
            : "=a"(status)
            : "d"(ATA_PRIMARY_BASE + 0x7)
        );
    } while(status & 0x80);
}

void ata_read_sector(unsigned int lba, unsigned char *buffer) {
    ata_wait();
    
    unsigned char cmd = 0x40 | ((lba >> 24) & 0x0F);
    __asm__ volatile("outb %%al, %%dx" : : "a"(cmd), "d"(ATA_PRIMARY_BASE + 0x6));
    
    __asm__ volatile("outb %%al, %%dx" : : "a"(1), "d"(ATA_PRIMARY_BASE + 0x2));
    
    cmd = lba & 0xFF;
    __asm__ volatile("outb %%al, %%dx" : : "a"(cmd), "d"(ATA_PRIMARY_BASE + 0x3));
    
    cmd = (lba >> 8) & 0xFF;
    __asm__ volatile("outb %%al, %%dx" : : "a"(cmd), "d"(ATA_PRIMARY_BASE + 0x4));
    
    cmd = (lba >> 16) & 0xFF;
    __asm__ volatile("outb %%al, %%dx" : : "a"(cmd), "d"(ATA_PRIMARY_BASE + 0x5));
    
    __asm__ volatile("outb %%al, %%dx" : : "a"(ATA_CMD_READ), "d"(ATA_PRIMARY_BASE + 0x7));
    
    ata_wait();
    
    for(int i = 0; i < 256; i++) {
        unsigned short data;
        __asm__ volatile("inw %%dx, %%ax" : "=a"(data) : "d"(ATA_PRIMARY_BASE));
        buffer[i*2] = data & 0xFF;
        buffer[i*2+1] = (data >> 8) & 0xFF;
    }
}