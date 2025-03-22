/*
 * BearOS - Wi-Fi Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef WIFI_DRIVER_H
#define WIFI_DRIVER_H

// Define tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Estados de conexión Wi-Fi
#define WIFI_STATE_DISCONNECTED 0
#define WIFI_STATE_CONNECTED    1
#define WIFI_STATE_CONNECTING   2

// Configuración básica de red
typedef struct {
    char ssid[32];       // Nombre de la red
    char password[64];   // Contraseña de la red
} WiFiConfig;

// Inicializa el controlador Wi-Fi
void wifi_init();

// Conecta a una red Wi-Fi
uint8_t wifi_connect(WiFiConfig* config);

// Desconecta de la red actual
void wifi_disconnect();

// Envía datos a través de la red Wi-Fi
uint8_t wifi_send(const uint8_t* data, uint32_t length);

// Recibe datos desde la red Wi-Fi
uint8_t wifi_receive(uint8_t* buffer, uint32_t length);

#endif // WIFI_DRIVER_H
