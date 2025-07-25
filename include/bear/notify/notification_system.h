/*
 * BearOS - Notification System Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef NOTIFICATION_SYSTEM_H
#define NOTIFICATION_SYSTEM_H

#include "../../../fs/k_printf.h"

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

#define NOTIF_TYPE_INFO     0x01
#define NOTIF_TYPE_WARNING  0x02
#define NOTIF_TYPE_ERROR    0x03

#define MAX_NOTIFICATIONS 32

typedef struct {
    uint8_t type;          // type notification (INFO, WARNING, ERROR)
    const char* message;   // notification message.
} Notification;

void notif_system_init();

void send_notification(uint8_t type, const char* message);

void list_notifications();

void clear_notifications();

#endif // NOTIFICATION_SYSTEM_H
