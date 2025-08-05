#include "i3c.h"
#include "../../io/global.h"
#include "../../delay/delay.h"

#define NULL ((void*)0)  
static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline void outl(unsigned short port, unsigned int value) {
    asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

#define I3C_CONTROL_REG      (I3C_PORT_BASE + 0x00)
#define I3C_STATUS_REG       (I3C_PORT_BASE + 0x04)
#define I3C_DATA_REG         (I3C_PORT_BASE + 0x08)
#define I3C_CCC_REG          (I3C_PORT_BASE + 0x0C)
#define I3C_DEVICE_ADDR_REG  (I3C_PORT_BASE + 0x10)

#define I3C_STATUS_READY     0x01
#define I3C_STATUS_BUSY      0x02
#define I3C_STATUS_IBI_PEND  0x04
#define I3C_STATUS_ERROR     0x80

int i3c_init(uint8_t port_num, uint32_t max_speed) {
    uint32_t base = I3C_PORT_BASE + (port_num * 0x20);
    
    // Resetear controlador
    outb(I3C_CONTROL_REG + base, 0x80);
    delay(10);
    outb(I3C_CONTROL_REG + base, 0x00);
    
    // Configurar velocidad
    outl(I3C_CONTROL_REG + base + 0x04, max_speed);
    
    // Habilitar controlador
    outb(I3C_CONTROL_REG + base, 0x01);
    
    return 0;
}

int i3c_ccc_send(uint8_t port_num, uint8_t ccc_code, uint8_t *data, uint32_t len) {
    uint32_t base = I3C_PORT_BASE + (port_num * 0x20);
    
    // Esperar hasta que el bus esté listo
    while ((inb(I3C_STATUS_REG + base) & I3C_STATUS_BUSY)) {
        delay(1);
    }
    
    // Enviar código CCC
    outb(I3C_CCC_REG + base, ccc_code);
    outb(I3C_CONTROL_REG + base, 0x08); // Enviar CCC
    
    // Si hay datos asociados al CCC
    if (len > 0 && data != NULL) {
        for (uint32_t i = 0; i < len; i++) {
            outb(I3C_DATA_REG + base, data[i]);
            outb(I3C_CONTROL_REG + base, 0x02); // Enviar dato
            
            if ((inb(I3C_STATUS_REG + base) & I3C_STATUS_ERROR)) {
                return -1;
            }
        }
    }
    return 0;
}


int i3c_write(uint8_t port_num, uint8_t target_addr, uint8_t *data, uint32_t len) {
    uint32_t base = I3C_PORT_BASE + (port_num * 0x20);
    
    // Configurar dirección de destino
    outb(I3C_DEVICE_ADDR_REG + base, target_addr);
    
    // Enviar datos
    for (uint32_t i = 0; i < len; i++) {
        outb(I3C_DATA_REG + base, data[i]);
        outb(I3C_CONTROL_REG + base, 0x02); // Enviar dato
        
        if ((inb(I3C_STATUS_REG + base) & I3C_STATUS_ERROR)) {
            return -1;
        }
    }
    
    return len;
}