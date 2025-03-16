#include "gpio_driver.h"

// Simulación de registros GPIO (cada bit representa un pin)
#define GPIO_PORT_MODE  0x00FF // Registro de modo: 0 = entrada, 1 = salida
#define GPIO_PORT_STATE 0x00AA // Registro de estado: 0 = bajo, 1 = alto

static uint32_t gpio_mode_register = 0;  // Modo de los pines GPIO
static uint32_t gpio_state_register = 0; // Estado de los pines GPIO

// Inicializa el controlador GPIO
void gpio_init() {
    gpio_mode_register = 0x0;  // Todos los pines en modo entrada por defecto
    gpio_state_register = 0x0; // Todos los pines en estado bajo
}

// Configura el modo de un pin GPIO
void gpio_set_mode(uint8_t pin, uint8_t mode) {
    if (mode == GPIO_MODE_OUTPUT) {
        gpio_mode_register |= (1 << pin); // Configurar como salida
    } else {
        gpio_mode_register &= ~(1 << pin); // Configurar como entrada
    }
}

// Escribe en un pin GPIO configurado como salida
void gpio_write(uint8_t pin, uint8_t value) {
    if (gpio_mode_register & (1 << pin)) { // Verifica si el pin está en modo salida
        if (value == GPIO_HIGH) {
            gpio_state_register |= (1 << pin); // Establece el pin en alto
        } else {
            gpio_state_register &= ~(1 << pin); // Establece el pin en bajo
        }
    }
}

// Lee el estado de un pin GPIO configurado como entrada
uint8_t gpio_read(uint8_t pin) {
    if (!(gpio_mode_register & (1 << pin))) { // Verifica si el pin está en modo entrada
        return (gpio_state_register & (1 << pin)) ? GPIO_HIGH : GPIO_LOW;
    }
    return GPIO_LOW; // Si no está en modo entrada, retorna bajo por defecto
}
