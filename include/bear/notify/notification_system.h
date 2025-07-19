/*
 * BearOS - Notification System Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef NOTIFICATION_SYSTEM_H
#define NOTIFICATION_SYSTEM_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Tipos de notificaciones
#define NOTIF_TYPE_INFO     0x01
#define NOTIF_TYPE_WARNING  0x02
#define NOTIF_TYPE_ERROR    0x03

// Máximo de notificaciones que pueden almacenarse
#define MAX_NOTIFICATIONS 32

// Estructura de una notificación
typedef struct {
    uint8_t type;          // Tipo de notificación (INFO, WARNING, ERROR)
    const char* message;   // Mensaje de la notificación
} Notification;

// Inicializa el sistema de notificaciones
void notif_system_init();

// Envía una notificación al sistema
void send_notification(uint8_t type, const char* message);

// Lista todas las notificaciones almacenadas
void list_notifications();

// Limpia todas las notificaciones almacenadas
void clear_notifications();

#endif // NOTIFICATION_SYSTEM_H
