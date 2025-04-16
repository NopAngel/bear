/*
*
*   panic.h - a generic file for panic
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/


#ifndef KERNEL_PANIC_H
#define KERNEL_PANIC_H

#include "../fs/k_printf.h"
unsigned int kernelPanic(const char** reasons);

#endif
