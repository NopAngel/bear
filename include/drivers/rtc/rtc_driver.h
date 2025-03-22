/*
 * BearOS - RTC Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef RTC_DRIVER_H
#define RTC_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Registros del RTC
#define RTC_ADDRESS_PORT 0x70
#define RTC_DATA_PORT    0x71

// Funciones del controlador RTC
void rtc_init();
void rtc_get_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds);
void rtc_get_date(uint8_t* day, uint8_t* month, uint8_t* year);

#endif // RTC_DRIVER_H
