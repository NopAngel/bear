#ifndef GETTIME_H
#define GETTIME_H
typedef unsigned int uint32_t;

#include "../../fs/clear_screen.h"
#include "../../fs/k_printf.h"

unsigned char read_cmos(unsigned char reg);
uint32_t get_time(void);

#endif