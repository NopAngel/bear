led_driver.c#include "led_driver.h"

// Puntero para almacenar el estado del LED
static uint8_t* led_state = (void*)0;

// Inicializa el LED asignando un espacio en memoria
void led_init(uint8_t* led_memory) {
    led_state = led_memory;
    *led_state = LED_OFF; // El LED comienza apagado
}

// Enciende el LED
void led_turn_on() {
    if (led_state != (void*)0) {
        *led_state = LED_ON;
    }
}

// Apaga el LED
void led_turn_off() {
    if (led_state != (void*)0) {
        *led_state = LED_OFF;
    }
}

// Obtiene el estado actual del LED
uint8_t led_get_state() {
    if (led_state != (void*)0) {
        return *led_state;
    }
    return LED_OFF; // Valor predeterminado
}
