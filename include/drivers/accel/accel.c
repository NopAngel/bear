

#include "accel.h"
#include "../../../fs/k_printf.h"

#define RED_TXT 0x04
#define GREEN_TXT 0x02

typedef unsigned int uint32_t;  

#define ACCEL_BASE_ADDR  0xE0000000 
#define ACCEL_REG_STATUS  (ACCEL_BASE_ADDR + 0x00)
#define ACCEL_REG_COMMAND (ACCEL_BASE_ADDR + 0x04)
#define ACCEL_REG_DATA    (ACCEL_BASE_ADDR + 0x08)
#define ACCEL_REG_CONFIG  (ACCEL_BASE_ADDR + 0x0C)

#define ACCEL_CMD_INIT    0x01
#define ACCEL_CMD_START   0x02
#define ACCEL_CMD_STOP    0x03
#define ACCEL_CMD_RESET   0x04

#define ACCEL_STATUS_READY  (1 << 0)
#define ACCEL_STATUS_BUSY   (1 << 1)
#define ACCEL_STATUS_ERROR  (1 << 2)


static inline uint32_t accel_read_reg(uint32_t reg) {
    return *((volatile uint32_t*)reg);  
}

static inline void accel_write_reg(uint32_t reg, uint32_t value) {
    *((volatile uint32_t*)reg) = value;  
}

int accel_init() {
    
    uint32_t status = accel_read_reg(ACCEL_REG_STATUS);
    
    if (!(status & ACCEL_STATUS_READY)) {
        k_printf("ACCEL: device not found", 0, RED_TXT);
        return -1;
    }


    accel_write_reg(ACCEL_REG_COMMAND, ACCEL_CMD_INIT);

    while (accel_read_reg(ACCEL_REG_STATUS) & ACCEL_STATUS_BUSY) {
        asm volatile("pause"); 
    }

    k_printf("ACCEL: inited!", 0, GREEN_TXT);
    return 0;
}

int accel_execute(uint32_t *input, uint32_t *output, uint32_t size) {
    // verify
    if (!(accel_read_reg(ACCEL_REG_STATUS) & ACCEL_STATUS_READY)) {
        k_printf("ACCEL: It's not ready", 0, RED_TXT);
        return -1;
    }

    // config size
    accel_write_reg(ACCEL_REG_CONFIG, size);

    // writting data
    for (uint32_t i = 0; i < size; i++) {
        accel_write_reg(ACCEL_REG_DATA, input[i]);
    }

    // started operation
    accel_write_reg(ACCEL_REG_COMMAND, ACCEL_CMD_START);

    // waiting
    while (accel_read_reg(ACCEL_REG_STATUS) & ACCEL_STATUS_BUSY) {
        asm volatile("pause");
    }

    for (uint32_t i = 0; i < size; i++) {
        output[i] = accel_read_reg(ACCEL_REG_DATA);
    }

    return 0;
}

void accel_stop() {
    accel_write_reg(ACCEL_REG_COMMAND, ACCEL_CMD_STOP);
}

void accel_reset() {
    accel_write_reg(ACCEL_REG_COMMAND, ACCEL_CMD_RESET);
}

/*

HOW TO USE?

uint32_t input_data[4] = {1, 2, 3, 4};
uint32_t output_data[4] = {0};

if (accel_execute(input_data, output_data, 4) == 0) {
    k_printf("Result: %d %d %d %d\n", 0, WHITE_TXT, 
             output_data[0], output_data[1], output_data[2], output_data[3]);
}

*/