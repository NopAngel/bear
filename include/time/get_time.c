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



void get_time() {
    unsigned char hours = read_cmos(0x04);
    unsigned char minutes = read_cmos(0x02);
    unsigned char seconds = read_cmos(0x00);
    char time_str[3]; 
    time_str[0] = (hours / 10) + '0'; 
    time_str[1] = (hours % 10) + '0'; 
    time_str[2] = '\0'; 

    char seconds_str[3]; 
    seconds_str[0] = (seconds / 10) + '0'; 
    seconds_str[1] = (seconds % 10) + '0'; 
    seconds_str[2] = '\0';

    char minutes_str[3]; 
    minutes_str[0] = (minutes / 10) + '0'; 
    minutes_str[1] = (minutes % 10) + '0'; 
    minutes_str[2] = '\0';

    k_clear_screen();
    k_printf(time_str, GREEN_TXT, 0);
    k_printf(minutes_str, GREEN_TXT, 1);
    k_printf(seconds_str, GREEN_TXT, 2); // THIS IS A BUG :,V
}
