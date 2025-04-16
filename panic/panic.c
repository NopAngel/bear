/*
*
*   panic.c - a generic file for panic
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/


// WARNING: I know this needs fixing, but I'm too lazy. I'll do it later. :)




void kernelPanic(char * reasons) {
	asm volatile("cli");
	k_printf(reasons, 0x04, 0);
}

