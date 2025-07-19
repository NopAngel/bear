
#define LED_REGISTER (*(volatile unsigned int *)0x40020000)
#define LED_ON  1
#define LED_OFF 0


void init_led() {
    LED_REGISTER = 0; 
}

void turn_on_led() {
    LED_REGISTER = LED_ON; 
}


void turn_off_led() {
    LED_REGISTER = LED_OFF; 
}


/*

    HOW TO USE???
    :
void main() {
    init_led();
    turn_on_led();

    for (volatile unsigned int i = 0; i < 1000000; i++);

    turn_off_led();
    while (1); 
}
*/