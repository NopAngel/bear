/*
 * BearOS - Battery Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef BATTERY_DRIVER_H
#define BATTERY_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Estados de la batería
#define BATTERY_STATE_CHARGING    0x01
#define BATTERY_STATE_DISCHARGING 0x02
#define BATTERY_STATE_FULL        0x03
#define BATTERY_STATE_UNKNOWN     0xFF

// Estructura para información de la batería
typedef struct {
    uint8_t state;      // Estado actual de la batería
    uint8_t charge;     // Porcentaje de carga (0-100)
    uint32_t voltage;   // Voltaje en mV
    uint32_t capacity;  // Capacidad restante en mAh
} BatteryStatus;

// Inicializa el controlador de batería
void battery_init();

// Obtiene el estado actual de la batería
void battery_get_status(BatteryStatus* status);

#endif // BATTERY_DRIVER_H
