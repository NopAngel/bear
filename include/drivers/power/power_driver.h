/*
 * BearOS - Power Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef POWER_DRIVER_H
#define POWER_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;

// Opciones de energía
#define POWER_OFF    0x00
#define POWER_REBOOT 0x01
#define POWER_SLEEP  0x02

// Inicializa el controlador de energía
void power_init();

// Apaga el sistema
void power_shutdown();

// Reinicia el sistema
void power_reboot();

// Suspende el sistema
void power_sleep();

#endif // POWER_DRIVER_H
