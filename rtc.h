#pragma once

// Tipos básicos
typedef unsigned char u8;
typedef unsigned int  u32;

// Estructura simple para almacenar fecha y hora
typedef struct {
    u8 second;
    u8 minute;
    u8 hour;
    u8 day;
    u8 month;
    u32 year;
} rtc_time_t;

// Funciones
void rtc_init();                // (opcional si querés configurar interrupts más adelante)
rtc_time_t rtc_get_time();      // Retorna hora actual
void rtc_format_time(char* buf, rtc_time_t* time); // Devuelve "HH:MM:SS"

