
#include "led_driver.h"

void main() {
    init_led();
    turn_on_led();
    for (volatile unsigned int i = 0; i < 1000000; i++);
    turn_off_led();
    while (1); 
}