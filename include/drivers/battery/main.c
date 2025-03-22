#include "battery_driver.h"

int main() {
    // Inicializa el controlador de batería
    battery_init();

    // Obtén el estado actual de la batería
    BatteryStatus status;
    battery_get_status(&status);

    // Toma decisiones según el estado de la batería
    if (status.charge < 20) {
        k_printf("Advertencia: Batería baja (%d%%).\n", 20, 0x0C); // Línea 20, rojo
    }

    if (status.state == BATTERY_STATE_CHARGING) {
        k_printf("Batería cargando.\n", 21, 0x0A); // Línea 21, verde
    }

    return 0;
}
