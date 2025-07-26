#include "wmsg.h"

void W_MSG() {
    k_clear_screen();
    k_printf("root@bear", 0, WHITE_TXT);
    k_printf("---------", 1, WHITE_TXT);
    k_printf("OS: BearOS x86 (KERNEL)", 2, WHITE_TXT);
    k_printf("Shell: bash_bear x86_64", 3, WHITE_TXT);
    k_printf("FileSystem: FAT32 (default)", 4, WHITE_TXT);
    
    // COLORS in TEXT.
    
    k_printf_xy("OS",0, 2, RED_TXT);
    k_printf_xy("Shell",0, 3, RED_TXT);
    k_printf_xy("FileSystem",0, 4, RED_TXT);
    
    k_printf_xy("  ", 6,6, BLACK_BG);
    k_printf_xy("  ", 8,6, GRAY_BG);
    k_printf_xy("  ", 10,6, RED_BG);
    k_printf_xy("  ", 12,6, ORANGE_BG);
    k_printf_xy("  ", 14,6, PINK_BG);
   

    
}
