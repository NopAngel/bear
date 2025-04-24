     1                                  ;
     2                                  ;
     3                                  ;   kernel.asm - the main file for ruuning kernel (bootloader style)
     4                                  ;
     5                                  ;  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
     6                                  ;
     7                                  ;           This code is licenced under the APACHE 2.0
     8                                  ;
     9                                  
    10                                  
    11                                  bits 32		;nasm directive
    12                                  section .text
    13                                  	;multiboot spec
    14                                  	align 4
    15 00000000 02B0AD1B                	dd 0x1BADB002			;magic
    16 00000004 00000000                	dd 0x00				;flags
    17 00000008 FE4F52E4                	dd - (0x1BADB002 + 0x00)	;checksum. m+f+c should be zero
    18                                  
    19                                  global start
    20                                  extern k_main	;k_main is defined in the kernel.c file
    21                                  global load_idt
    22                                  
    23                                  load_idt:
    24 0000000C 0F0118                      lidt [eax]  ; Carga la IDT desde el puntero en EAX
    25 0000000F C3                          ret
    26                                  
    27                                  start:
    28 00000010 FA                      	cli  ; stop interrupts
    29                                  
    30 00000011 E8(00000000)            	call k_main
    31                                  
    32 00000016 F4                      	hlt ; halt the CPU
