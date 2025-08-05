#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include "../../type.h"

#define I2C_PORT_BASE 0x9000  // Puerto base ficticio para I2C (ajustar según hardware real)

// Estructura para configuración I2C
typedef struct {
    uint32_t clock_speed;  // Velocidad en Hz
    uint8_t slave_address;
    uint8_t port_num;
} i2c_config_t;

// Funciones principales
int i2c_init(uint8_t port_num, uint32_t clock_speed);
int i2c_write(uint8_t port_num, uint8_t slave_addr, uint8_t *data, uint32_t len);
int i2c_read(uint8_t port_num, uint8_t slave_addr, uint8_t *buffer, uint32_t len);
int i2c_scan(uint8_t port_num, uint8_t *devices, uint32_t max_devices);

// Funciones avanzadas
int i2c_set_clock(uint8_t port_num, uint32_t clock_speed);
int i2c_reset(uint8_t port_num);

#endif // I2C_DRIVER_H