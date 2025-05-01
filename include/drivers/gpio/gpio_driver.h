/*
 * BearOS - GPIO Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H


typedef unsigned char uint8_t;
typedef unsigned int uint32_t;


#define GPIO_MODE_INPUT  0
#define GPIO_MODE_OUTPUT 1

#define GPIO_LOW  0
#define GPIO_HIGH 1

void gpio_init();

void gpio_set_mode(uint8_t pin, uint8_t mode);


void gpio_write(uint8_t pin, uint8_t value);

uint8_t gpio_read(uint8_t pin);

#endif // GPIO_DRIVER_H
