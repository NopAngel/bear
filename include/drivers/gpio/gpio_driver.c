#include "gpio_driver.h"

#define GPIO_PORT_MODE  0x00FF 
#define GPIO_PORT_STATE 0x00AA 

static uint32_t gpio_mode_register = 0;  
static uint32_t gpio_state_register = 0; 


void gpio_init() {
    gpio_mode_register = 0x0;  
    gpio_state_register = 0x0; 
}


void gpio_set_mode(uint8_t pin, uint8_t mode) {
    if (mode == GPIO_MODE_OUTPUT) {
        gpio_mode_register |= (1 << pin); 
    } else {
        gpio_mode_register &= ~(1 << pin);
    }
}


void gpio_write(uint8_t pin, uint8_t value) {
    if (gpio_mode_register & (1 << pin)) { 
        if (value == GPIO_HIGH) {
            gpio_state_register |= (1 << pin);
        } else {
            gpio_state_register &= ~(1 << pin); 
        }
    }
}


uint8_t gpio_read(uint8_t pin) {
    if (!(gpio_mode_register & (1 << pin))) { /
        return (gpio_state_register & (1 << pin)) ? GPIO_HIGH : GPIO_LOW;
    }
    return GPIO_LOW; 
}
