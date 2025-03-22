#include "input_driver.h"

int main() {
    // Inicializa los controladores
    input_init();


    // Maneja eventos de entrada simulados
    input_handle_keyboard(42);   // Simula una tecla presionada
    input_handle_mouse(10, -5, 1); // Simula un movimiento del mouse

    // Verifica si hay eventos en cola
    if (input_poll_event()) {
        k_printf("Evento de entrada disponible.\n", 30, 0x0F); // Línea 30
    }

    return 0;
}
