/*
 * BearOS - Time System Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Estructura de un evento basado en tiempo
typedef struct {
    uint8_t hour;         // Hora específica (24h formato)
    uint8_t minute;       // Minuto específico
    uint8_t second;       // Segundo específico
    void (*action)(void); // Función a ejecutar
} TimeEvent;

// Inicializa el sistema de tiempo
void time_system_init();

// Registra un evento basado en tiempo
void register_time_event(TimeEvent event);

// Verifica si un evento debe ejecutarse (debería llamarse periódicamente)
void process_time_events();

#endif // TIME_SYSTEM_H
