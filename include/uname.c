#include "uname.h"

void uname() {
    
    k_clear_screen();
    int cursor_y = 0;
    k_printf("BearOS Information:", cursor_y++, CYAN_TXT);
    k_printf("------------------", cursor_y++, CYAN_TXT);
    k_printf("Kernel Name: BearOS", cursor_y++, WHITE_TXT);
    k_printf("Kernel Version: 2.0", cursor_y++, WHITE_TXT);
    k_printf("Architecture: x86", cursor_y++, WHITE_TXT);
    k_printf("Author: NopAngel", cursor_y++, WHITE_TXT);
    k_printf("License: Apache 2.0", cursor_y++, WHITE_TXT);
    cursor_y++;
}
