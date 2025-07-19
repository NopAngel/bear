#include "pnp.h"

// Variables globales (o podés retornarlas en una struct si lo preferís)
uint32_t cseg_size = 0;
uint32_t offset = 0;
uint32_t base_addr = 0;

// Dirección ficticia a la que se hará LCALL (¡reemplazá esto por la real!)
volatile uint16_t bios32_selector = 0x08;
volatile uint32_t bios32_offset = 0x1000;

extern "C" void bios32_scan_pnp_entry() {
    asm volatile(
        "movl $0x46434124, %%eax\n\t"        // '$ACF'
        "lcall *(%%edi)\n\t"                 // salta a selector:offset en EDI
        "movl %%ecx, %0\n\t"
        "movl %%edx, %1\n\t"
        "movl %%ebx, %2\n\t"
        : "=m"(cseg_size), "=m"(offset), "=m"(base_addr)
        : "D"(&bios32_offset)                // EDI apunta a [offset, selector]
        : "eax", "ebx", "ecx", "edx", "memory"
    );
}
