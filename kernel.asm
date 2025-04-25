;
;
;   kernel.asm - the main file for ruuning kernel (bootloader style)
;
;  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
;
;           This code is licenced under the APACHE 2.0
;


bits 32		;nasm directive
section .text
	;multiboot spec
	align 4
	dd 0x1BADB002			;magic
	dd 0x00				;flags
	dd - (0x1BADB002 + 0x00)	;checksum. m+f+c should be zero

global start
extern k_main	;k_main is defined in the kernel.c file
global load_idt

load_idt:
    lidt [eax]  ; Carga la IDT desde el puntero en EAX
    ret

start:
	cli  ; stop interrupts

	call k_main

	hlt ; halt the CPU