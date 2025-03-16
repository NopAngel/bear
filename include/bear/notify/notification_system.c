#include "notification_system.h"
#include "bear/k_print.h" // Para mostrar mensajes en el sistema

// Arreglo para almacenar notificaciones
static Notification notifications[MAX_NOTIFICATIONS];
static uint8_t notification_count = 0;

// Inicializa el sistema de notificaciones
void notif_system_init() {
    notification_count = 0;
    k_printf("Sistema de notificaciones inicializado.\n", 10, 0x0A); // Línea 10, verde
}

// Envía una notificación al sistema
void send_notification(uint8_t type, const char* message) {
    if (notification_count >= MAX_NOTIFICATIONS) {
        k_printf("Error: Límite de notificaciones alcanzado.\n", 11, 0x04); // Línea 11, rojo
        return;
    }

    // Almacena la notificación
    notifications[notification_count].type = type;
    notifications[notification_count].message = message;
    notification_count++;

    // Muestra la notificación instantáneamente
    switch (type) {
        case NOTIF_TYPE_INFO:
            k_printf("INFO: %s\n", 12, 0x07); // Línea 12, blanco
            break;
        case NOTIF_TYPE_WARNING:
            k_printf("WARNING: %s\n", 13, 0x0E); // Línea 13, amarillo
            break;
        case NOTIF_TYPE_ERROR:
            k_printf("ERROR: %s\n", 14, 0x0C); // Línea 14, rojo
            break;
        default:
            k_printf("UNKNOWN: %s\n", 15, 0x07); // Línea 15, blanco
            break;
    }
}

// Lista todas las notificaciones almacenadas
void list_notifications() {
    k_printf("Notificaciones almacenadas:\n", 16, 0x07); // Línea 16, blanco
    for (uint8_t i = 0; i < notification_count; i++) {
        const char* type_str = "UNKNOWN";
        switch (notifications[i].type) {
            case NOTIF_TYPE_INFO:
                type_str = "INFO";
                break;
            case NOTIF_TYPE_WARNING:
                type_str = "WARNING";
                break;
            case NOTIF_TYPE_ERROR:
                type_str = "ERROR";
                break;
        }
        k_printf("[%s] %s\n", 17 + i, 0x07); // Línea incremental
    }
}

// Limpia todas las notificaciones almacenadas
void clear_notifications() {
    notification_count = 0;
    k_printf("Todas las notificaciones han sido eliminadas.\n", 18, 0x0A); // Línea 18, verde
}
