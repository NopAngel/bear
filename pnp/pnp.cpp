#include "pnp.h"


uint32_t cseg_size = 0;
uint32_t offset = 0;
uint32_t base_addr = 0;


volatile uint16_t bios32_selector = 0x08;
volatile uint32_t bios32_offset = 0x1000;

extern "C" void bios32_scan_pnp_entry() {
    asm volatile(
        "movl $0x46434124, %%eax\n\t"        
        "lcall *(%%edi)\n\t"                
        "movl %%ecx, %0\n\t"
        "movl %%edx, %1\n\t"
        "movl %%ebx, %2\n\t"
        : "=m"(cseg_size), "=m"(offset), "=m"(base_addr)
        : "D"(&bios32_offset)               
        : "eax", "ebx", "ecx", "edx", "memory"
    );
}
