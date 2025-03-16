#include "kernel.h"

int main() {
    // Inicializa el kernel
    kernel_init();

    // Manejo simulado de interrupciones
    kernel_handle_interrupt(2); // Enciende el LED
    kernel_handle_interrupt(1); // Apaga el LED

    // Inicia el loop principal del kernel
    kernel_main_loop();

    return 0;
}
