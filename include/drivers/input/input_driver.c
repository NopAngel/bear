#include "input_driver.h"
#include "bear/k_print.h"

// Simula un buffer de entrada
static uint8_t input_buffer[256];
static uint8_t input_buffer_size = 0;

// Inicializa el controlador de entrada
void input_init() {
    input_buffer_size = 0;
    k_printf("Controlador de entrada inicializado.\n", 10, 0x0A); // Línea 10, verde
}

// Maneja eventos de teclado
void input_handle_keyboard(uint8_t scan_code) {
    if (input_buffer_size < 256) {
        input_buffer[input_buffer_size++] = scan_code; // Almacena el código
        k_printf("Teclado: Codigo %d recibido.\n", 11, 0x07); // Línea 11
    }
}

// Maneja eventos de mouse
void input_handle_mouse(uint8_t x_delta, uint8_t y_delta, uint8_t buttons) {
    if (input_buffer_size < 256) {
        input_buffer[input_buffer_size++] = x_delta;
        input_buffer[input_buffer_size++] = y_delta;
        input_buffer[input_buffer_size++] = buttons;
        k_printf("Mouse: Movimiento (%d, %d), Botones %d.\n", 12, 0x07); // Línea 12
    }
}

// Verifica si hay entradas disponibles
uint8_t input_poll_event() {
    return (input_buffer_size > 0);
}
