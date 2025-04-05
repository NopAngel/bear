#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

unsigned int k_printf_r(char *message, unsigned int line, unsigned int color);
unsigned int kernelPanic(const char** reasons);

#endif
