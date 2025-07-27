#ifndef CRW_H
#define CRW_H


#include "../../fs/k_printf.h" 

#define BOOTLOG_OK     0
#define BOOTLOG_FAIL   1
#define BOOTLOG_INFO   2

#define LOG_COLOR_OK   0x0A  
#define LOG_COLOR_FAIL 0x0C 
#define LOG_COLOR_INFO 0x0B  
#define LOG_COLOR_TEXT 0x07 


void bootlog(const char *message, int status);

#endif