#include "crw.h"

#include "../../fs/k_printf.h" 
#include "../delay/delay.h"


#define GREEN_TXT 0x02
#define YELLOW_TXT 0x0E
#define RED_TXT 0x04

#define WHITE_TXT 0x07

void CR_W(const char *message, int status, unsigned int line) {
    const char *status_str;
    unsigned int color;

    switch (status) {
        case GREEN_TXT:
            status_str = "[  OK  ]";
            color = GREEN_TXT;
            break;
        case RED_TXT:
            status_str = "[ FAIL ]";
            color = RED_TXT;
            break;
        case YELLOW_TXT:
            status_str = "[ INFO ]";
            color = YELLOW_TXT;
            break;
        default:
            status_str = "[  ??  ]";
            color = WHITE_TXT;
    }

    k_printf_xy(status_str, 0, line, color);
    k_printf_xy(message, 9, line, WHITE_TXT);  
    delay(10);
}