#include "notification_system.h"

int main() {
    // Inicializa el sistema de notificaciones
    notif_system_init();

    // Envía algunas notificaciones
    send_notification(NOTIF_TYPE_INFO, "BearOS está funcionando correctamente.");
    send_notification(NOTIF_TYPE_WARNING, "Espacio en disco bajo.");
    send_notification(NOTIF_TYPE_ERROR, "Error crítico en el sistema.");

    // Lista las notificaciones
    list_notifications();

    // Limpia las notificaciones
    clear_notifications();

    return 0;
}
