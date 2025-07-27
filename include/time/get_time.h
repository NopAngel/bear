#ifndef GETTIME_H
#define GETTIME_H

#include "../../fs/clear_screen.h"
#include "../../fs/k_printf.h"

unsigned char read_cmos(unsigned char reg);
void get_time();

#endif