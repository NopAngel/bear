#include "battery_driver.h"

int main() {
    // init for controller
    battery_init();

    // obtain state 
    BatteryStatus status;
    battery_get_status(&status);


    if (status.charge < 20) {
        k_printf("Advertencia: Batería baja (%d%%).\n", 20, 0x0C); 
    }

    if (status.state == BATTERY_STATE_CHARGING) {
        k_printf("Batería cargando.\n", 21, 0x0A); 
    }

    return 0;
}
