#include "kernel.h"
#include "led_driver.h"

// Memoria para el driver del LED
uint8_t led_memory;

// Inicializa el kernel
void kernel_init() {
    // Inicializa el controlador del LED
    led_init(&led_memory);

    // Enciende el LED al iniciar (indicando que el kernel está activo)
    led_turn_on();
}

// Maneja interrupciones simuladas
void kernel_handle_interrupt(uint8_t interrupt_code) {
    if (interrupt_code == 1) {
        // Simula apagar el LED ante una interrupción específica
        led_turn_off();
    } else if (interrupt_code == 2) {
        // Simula encender el LED ante otra interrupción
        led_turn_on();
    }
}

// Loop principal del kernel
void kernel_main_loop() {
    while (1) {
        // Aquí irían las tareas principales del kernel
        // Por ejemplo, verificar interrupciones o manejar eventos
    }
}
