#include "get_time.h"


#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71
#define GREEN_TXT 0x02

unsigned char read_cmos(unsigned char reg) {
    asm volatile (
        "mov %1, %%dx\n\t"
        "mov %2, %%al\n\t"
        "out %%al, %%dx\n\t"
        "mov %3, %%dx\n\t"
        "in %%dx, %%al\n\t"
        : "=a" (reg)
        : "i" (CMOS_ADDRESS), "r" (reg), "i" (CMOS_DATA)
        : "dx"
    );
    return reg;
}



uint32_t get_time(void) {
    return 0;
}
