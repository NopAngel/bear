#include "battery_driver.h"
#include "bear/k_print.h" 


static BatteryStatus battery_status = {
    .state = BATTERY_STATE_UNKNOWN,
    .charge = 0,
    .voltage = 0,
    .capacity = 0
};


void battery_init() {
    battery_status.state = BATTERY_STATE_CHARGING; 
    battery_status.charge = 75;                    
    battery_status.voltage = 11400;                
    battery_status.capacity = 5000;               
    k_printf("Controlador de batería inicializado.\n", 10, 0x0A); 
}


void battery_get_status(BatteryStatus* status) {
    if (status) {
        status->state = battery_status.state;
        status->charge = battery_status.charge;
        status->voltage = battery_status.voltage;
        status->capacity = battery_status.capacity;
        k_printf("Batería: %d%%, Voltaje: %dmV, Capacidad: %dmAh\n", 11, 0x07);
    } else {
        k_printf("Error: No se pudo obtener el estado de la batería.\n", 12, 0x04); 
    }
}
