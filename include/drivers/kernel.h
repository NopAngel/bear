#ifndef KERNEL_H
#define KERNEL_H

// Define tipos básicos
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// Inicializa el kernel y sus subsistemas
void kernel_init();

// Manejo de interrupciones (simulado en este caso)
void kernel_handle_interrupt(uint8_t interrupt_code);

// Loop principal del kernel
void kernel_main_loop();

#endif
