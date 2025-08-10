#include "../fs/k_printf.h"

void reboot_system() {
    
    // func for reboot system
    __asm__ volatile("cli");
    
    __asm__ volatile (
        "mov $0x13, %ax\n"
        "int $0x10\n"
    ); // mode vga :)
    
    __asm__ volatile (
        "ljmp $0xf000, $0xfff0"
    );

    while (1);
}

void denreboot() {
    k_printf("Reset BearOS...", 10, 0x0C);
    k_printf("Save data...", 11, 0x0C);

    for (int i = 0; i < 100000; i++) { asm volatile("nop"); }


    asm volatile (
        "cli;"           
        "movb $0xFE, %al;" 
        "outb %al, $0x64;" 
        "hlt;"             
    );
}
