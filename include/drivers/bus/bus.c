
#include "../../../fs/k_printf.h"
#define RED_TXT 0x04
#include "bus.h"

void bus_scan_pci() {
    for(unsigned int bus = 0; bus < 256; bus++) {
        for(unsigned int slot = 0; slot < 32; slot++) {
            unsigned int addr = 0x80000000 | (bus << 16) | (slot << 11);
            __asm__ volatile("outl %%eax, %%dx" : : "a"(addr), "d"(0xCF8));
            unsigned int data;
            __asm__ volatile("inl %%dx, %%eax" : "=a"(data) : "d"(0xCFC));
            if(data != 0xFFFFFFFF) {
                k_printf("BUS: Device not found", 0, RED_TXT);
            }
        }
    }
}