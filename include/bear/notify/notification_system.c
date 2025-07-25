#include "notification_system.h"

static Notification notifications[MAX_NOTIFICATIONS];
static uint8_t notification_count = 0;

void notif_system_init() {
    notification_count = 0;
    k_printf("Sistema de notificaciones inicializado.\n", 10, 0x0A); 
}

void send_notification(uint8_t type, const char* message) {
    if (notification_count >= MAX_NOTIFICATIONS) {
        k_printf("Error: Límite de notificaciones alcanzado.\n", 11, 0x04); 
        return;
    }

    notifications[notification_count].type = type;
    notifications[notification_count].message = message;
    notification_count++;


    switch (type) {
        case NOTIF_TYPE_INFO:
            k_printf(NOTIF_TYPE_INFO, 12, 0x07); 
            break;
        case NOTIF_TYPE_WARNING:
            k_printf(NOTIF_TYPE_WARNING, 13, 0x0E); 
            break;
        case NOTIF_TYPE_ERROR:
            k_printf(NOTIF_TYPE_ERROR, 14, 0x0C); 
            break;
        default:
            k_printf("UNKNOWN notify :(\n", 15, 0x07);
            break;
    }
}

// list all notify's
void list_notifications() {
    k_printf("Notification list:\n", 16, 0x07); // line 16, white
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
        k_printf("[%s] %s\n", 17 + i, 0x07); 
    }
}

void clear_notifications() {
    notification_count = 0;
    k_printf("Deleted all notifiy's.\n", 18, 0x0A); // line 18, green
}
