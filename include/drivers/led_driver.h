#ifndef LED_DRIVER_H
#define LED_DRIVER_H

// Define tipos básicos (reemplazo de stdint.h)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Estado del LED
#define LED_OFF 0
#define LED_ON  1

// Inicializa el controlador del LED
void led_init(uint8_t* led_memory);

// Enciende el LED
void led_turn_on();

// Apaga el LED
void led_turn_off();

// Obtiene el estado actual del LED
uint8_t led_get_state();

#endif
