/*
 * BearOS - Battery Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef BATTERY_DRIVER_H
#define BATTERY_DRIVER_H


typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

#define BATTERY_STATE_CHARGING    0x01
#define BATTERY_STATE_DISCHARGING 0x02
#define BATTERY_STATE_FULL        0x03
#define BATTERY_STATE_UNKNOWN     0xFF

typedef struct {
    uint8_t state;      
    uint8_t charge;     
    uint32_t voltage;   
    uint32_t capacity;  
} BatteryStatus;

void battery_init();

void battery_get_status(BatteryStatus* status);

#endif // BATTERY_DRIVER_H
