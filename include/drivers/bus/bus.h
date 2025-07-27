#ifndef _BUS_DRIVER_H
#define _BUS_DRIVER_H

typedef unsigned char uint32_t;
typedef unsigned char uint8_t;
typedef unsigned char uint16_t;


typedef struct {
    uint16_t vendor_id;
    uint16_t device_id;
} pci_device_t;


void bus_scan_pci();

#endif