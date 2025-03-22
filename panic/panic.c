#include "include/bear/k_printf.h"
#include "include/colors.h"

void kernelPanic(const char** reasons) {
	asm volatile("cli");
	k_printf("fatal exception: " + reasons, 0, RED_TXT);
}