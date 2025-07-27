#ifndef _ATM_DRIVER_H
#define _ATM_DRIVER_H

typedef unsigned char uint8_t;  
typedef unsigned char size_t;  


void *atm_alloc(size_t size);
void atm_free(void *ptr);

#endif