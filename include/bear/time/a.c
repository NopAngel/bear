#include "time_system.h"
#include "rtc_driver.h"
#include "bear/k_print.h"

// Acción a realizar en un evento
void ejemplo_accion() {
    k_printf("Evento activado: ¡Función de prueba ejecutada!\n", 20, 0x0F); // Línea 20, blanco brillante
}

int main() {
    // Inicializa los sistemas
    rtc_init();
    time_system_init();

    // Registra un evento para las 12:00:00
    TimeEvent evento = { .hour = 12, .minute = 0, .second = 0, .action = ejemplo_accion };
    register_time_event(evento);

    // Loop principal que procesa eventos en cada iteración
    while (1) {
        process_time_events();
    }

    return 0;
}
