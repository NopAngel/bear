/*
 * BearOS - USB Driver Header
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef USB_DRIVER_H
#define USB_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Estados del USB
#define USB_STATE_DISCONNECTED 0
#define USB_STATE_CONNECTED    1

// Inicializa los puertos USB
void usb_init();

// Detecta dispositivos conectados a los puertos USB
uint8_t usb_detect_device(uint8_t port);

// Envia datos al dispositivo USB
uint8_t usb_send_data(uint8_t port, const uint8_t* data, uint32_t length);

// Recibe datos desde un dispositivo USB
uint8_t usb_receive_data(uint8_t port, uint8_t* buffer, uint32_t length);

#endif // USB_DRIVER_H
