/*
 * BearOS - Input Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef INPUT_DRIVER_H
#define INPUT_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;

// Define tipos de eventos
#define INPUT_EVENT_KEYBOARD 0x01
#define INPUT_EVENT_MOUSE    0x02

// Inicializa el controlador de entrada
void input_init();

// Maneja eventos de teclado
void input_handle_keyboard(uint8_t scan_code);

// Maneja eventos de mouse
void input_handle_mouse(uint8_t x_delta, uint8_t y_delta, uint8_t buttons);

// Verifica si hay entradas disponibles (simulado)
uint8_t input_poll_event();

#endif // INPUT_DRIVER_H
