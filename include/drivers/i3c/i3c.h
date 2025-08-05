#ifndef I3C_DRIVER_H
#define I3C_DRIVER_H

#include "../../type.h"

#define I3C_PORT_BASE 0xA000  // Puerto base ficticio para I3C (ajustar según hardware real)

// Estructura para configuración I3C
typedef struct {
    uint32_t max_speed;    // Velocidad máxima en Hz
    uint8_t dynamic_addr;
    uint8_t static_addr;
    uint8_t port_num;
} i3c_config_t;

// Funciones principales
int i3c_init(uint8_t port_num, uint32_t max_speed);
int i3c_ccc_send(uint8_t port_num, uint8_t ccc_code, uint8_t *data, uint32_t len);
int i3c_write(uint8_t port_num, uint8_t target_addr, uint8_t *data, uint32_t len);
int i3c_read(uint8_t port_num, uint8_t target_addr, uint8_t *buffer, uint32_t len);
int i3c_ibi_handler(uint8_t port_num);  // Manejo de interrupciones IBI

// Funciones avanzadas
int i3c_assign_dynamic_addr(uint8_t port_num, uint8_t static_addr, uint8_t dyn_addr);
int i3c_reset_bus(uint8_t port_num);

#endif // I3C_DRIVER_H