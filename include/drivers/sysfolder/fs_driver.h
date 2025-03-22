#ifndef LED_DRIVER_H
#define LED_DRIVER_H


#define LED_REGISTER (*(volatile unsigned int *)0x40020000) 
#define LED_ON  1
#define LED_OFF 0

void init_led();   
void turn_on_led(); 
void turn_off_led();

#endif 
