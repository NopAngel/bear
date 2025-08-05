#include "i2c.h"
#include "../../io/global.h"
#include "../../delay/delay.h"

// Registros ficticios I2C (ajustar según hardware real)
#define I2C_CONTROL_REG   (I2C_PORT_BASE + 0x00)
#define I2C_STATUS_REG    (I2C_PORT_BASE + 0x04)
#define I2C_DATA_REG      (I2C_PORT_BASE + 0x08)
#define I2C_CLOCK_REG     (I2C_PORT_BASE + 0x0C)

// Estados del bus I2C
#define I2C_STATUS_READY  0x01
#define I2C_STATUS_BUSY   0x02
#define I2C_STATUS_ERROR  0x80

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

int i2c_init(uint8_t port_num, uint32_t clock_speed) {
    // Configurar velocidad del reloj
    outl(I2C_CLOCK_REG + (port_num * 0x10), 12000000 / clock_speed);
    
    // Habilitar el controlador I2C
    outb(I2C_CONTROL_REG + (port_num * 0x10), 0x01);
    
    return 0; // Éxito
}

int i2c_write(uint8_t port_num, uint8_t slave_addr, uint8_t *data, uint32_t len) {
    uint32_t base = I2C_PORT_BASE + (port_num * 0x10);
    
    // Esperar hasta que el bus esté listo
    while ((inb(I2C_STATUS_REG + base) & I2C_STATUS_BUSY)) {
        delay(1);
    }
    
    // Enviar dirección del esclavo (bit LSB = 0 para escritura)
    outb(I2C_DATA_REG + base, slave_addr << 1);
    outb(I2C_CONTROL_REG + base, 0x03); // Start + Write
    
    // Esperar ack
    while ((inb(I2C_STATUS_REG + base) & I2C_STATUS_BUSY));
    if ((inb(I2C_STATUS_REG + base) & I2C_STATUS_ERROR)) {
        return -1; // Error
    }
    
    // Enviar datos
    for (uint32_t i = 0; i < len; i++) {
        outb(I2C_DATA_REG + base, data[i]);
        outb(I2C_CONTROL_REG + base, 0x02); // Write
        
        if ((inb(I2C_STATUS_REG + base) & I2C_STATUS_ERROR)) {
            return -1; // Error
        }
    }
    
    // Enviar condición de stop
    outb(I2C_CONTROL_REG + base, 0x04);
    
    return len; // Bytes escritos
}

int i2c_read(uint8_t port_num, uint8_t slave_addr, uint8_t *buffer, uint32_t len) {
    uint32_t base = I2C_PORT_BASE + (port_num * 0x10);
    
    // Esperar hasta que el bus esté listo
    while ((inb(I2C_STATUS_REG + base) & I2C_STATUS_BUSY)) {
        delay(1);
    }
    
    // Enviar dirección del esclavo (bit LSB = 1 para lectura)
    outb(I2C_DATA_REG + base, (slave_addr << 1) | 0x01);
    outb(I2C_CONTROL_REG + base, 0x03); // Start + Write
    
    // Esperar ack
    while ((inb(I2C_STATUS_REG + base) & I2C_STATUS_BUSY));
    if ((inb(I2C_STATUS_REG + base) & I2C_STATUS_ERROR)) {
        return -1; // Error
    }
    
    // Leer datos
    for (uint32_t i = 0; i < len; i++) {
        outb(I2C_CONTROL_REG + base, (i == len - 1) ? 0x05 : 0x01); // Stop en último byte
        
        while ((inb(I2C_STATUS_REG + base) & I2C_STATUS_BUSY));
        buffer[i] = inb(I2C_DATA_REG + base);
    }
    
    return len; // Bytes leídos
}