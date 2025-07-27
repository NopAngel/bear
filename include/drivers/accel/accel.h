
#ifndef ACCEL_DRIVER_H
#define ACCEL_DRIVER_H

typedef unsigned int uint32_t;

int accel_init();
int accel_execute(uint32_t *input, uint32_t *output, uint32_t size);
void accel_stop();
void accel_reset();

#endif // _ACCEL_DRIVER_H