#include "time_system.h"
#include "rtc_driver.h"  // Para obtener la hora actual
#include "bear/k_print.h" // Para mostrar mensajes en el sistema

// Máximo de eventos que pueden almacenarse
#define MAX_TIME_EVENTS 16

// Almacena los eventos registrados
static TimeEvent time_events[MAX_TIME_EVENTS];
static uint8_t time_event_count = 0;

// Inicializa el sistema de tiempo
void time_system_init() {
    time_event_count = 0;
    k_printf("Sistema de tiempo inicializado.\n", 10, 0x0A); // Línea 10, verde
}

// Registra un evento basado en tiempo
void register_time_event(TimeEvent event) {
    if (time_event_count >= MAX_TIME_EVENTS) {
        k_printf("Error: Límite de eventos alcanzado.\n", 11, 0x04); // Línea 11, rojo
        return;
    }

    time_events[time_event_count++] = event;
    k_printf("Evento registrado para %02d:%02d:%02d.\n", 12, 0x07); // Línea 12, blanco
}

// Verifica si un evento debe ejecutarse
void process_time_events() {
    uint8_t hours, minutes, seconds;
    rtc_get_time(&hours, &minutes, &seconds); // Obtiene la hora actual desde el RTC

    for (uint8_t i = 0; i < time_event_count; i++) {
        TimeEvent* event = &time_events[i];
        if (event->hour == hours && event->minute == minutes && event->second == seconds) {
            k_printf("Ejecutando evento programado para %02d:%02d:%02d.\n", 13, 0x0A); // Línea 13, verde
            event->action(); // Ejecuta la función asociada
        }
    }
}
