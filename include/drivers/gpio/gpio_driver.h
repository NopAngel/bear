/*
 * BearOS - GPIO Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Modos del pin GPIO
#define GPIO_MODE_INPUT  0
#define GPIO_MODE_OUTPUT 1

// Estados del pin GPIO
#define GPIO_LOW  0
#define GPIO_HIGH 1

// Inicializa el controlador GPIO
void gpio_init();

// Configura el modo de un pin GPIO (entrada/salida)
void gpio_set_mode(uint8_t pin, uint8_t mode);

// Escribe un valor (alto/bajo) en un pin GPIO configurado como salida
void gpio_write(uint8_t pin, uint8_t value);

// Lee el estado (alto/bajo) de un pin GPIO configurado como entrada
uint8_t gpio_read(uint8_t pin);

#endif // GPIO_DRIVER_H
