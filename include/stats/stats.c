#include "../../fs/k_printf.h"
#include "../../fs/clear_screen.h"

#define ORANGE_TXT 0x06
#define WHITE_TXT 0x07
#define BLUE_TXT 0x09
#define AQUA_TXT 0x03 
#define GREEN_TXT 0x02

unsigned int get_ram_size() {
    unsigned int ram_size = 0x100000; 
    return ram_size / 1024; 
}


unsigned int get_disk_usage() {
    unsigned char usage;
    __asm__ __volatile__(
        "xor %%dx, %%dx\n\t"     
        "mov $0x1F0, %%dx\n\t"   
        "in %%dx, %%al\n\t"    
        "mov %%al, %0\n\t"     
        : "=r"(usage)
        :
        : "dx", "al"
    );
    return (unsigned int)usage * 512; 
}



unsigned int safe_mod(unsigned int dividend, unsigned int divisor) {
    return dividend - (divisor * (dividend / divisor));
}



void display_stats() {
    int cursor_y = 0;
    char buffer[32];
    unsigned int cpu_cycles = get_cpu_cycles();
    unsigned int ram_usage = get_ram_size(); 
    unsigned int disk_usage = get_disk_usage();

    k_clear_screen();
    k_printf("      MORE INFORMATION       ", cursor_y++, BLUE_TXT);

    k_printf("CPU Cycles:", cursor_y++, ORANGE_TXT);
    itoa(cpu_cycles, buffer, 10);
    k_printf(buffer, cursor_y++, AQUA_TXT);

    k_printf("RAM Usage (MB):", cursor_y++, GREEN_TXT);
    itoa(ram_usage, buffer, 10);
    k_printf(buffer, cursor_y++, AQUA_TXT);

    k_printf("Disk Usage (MB):", cursor_y++, BLUE_TXT);
    itoa(disk_usage, buffer, 10);
    k_printf(buffer, cursor_y++, AQUA_TXT);
}
