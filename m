     1                                  ;
     2                                  ;   kernel.asm - the main file for running kernel (Multiboot2 style with framebuffer)
     3                                  ;
     4                                  ;   (C) 2025 Ángel Nieto/NopAngel <angelnieto1402@gmail.com>
     5                                  ;
     6                                  ;   Licensed under the APACHE 2.0 License
     7                                  ;
     8                                  
     9                                  bits 32
    10                                  
    11                                  section .multiboot_header
    12                                  align 8
    13 00000000 D65052E8                    dd 0xE85250D6              ; Multiboot2 magic
    14 00000004 00000000                    dd 0                       ; i386
    15 00000008 1C000000                    dd header_end - header_start
    16 0000000C 0EAFAD17                    dd -(0xE85250D6 + 0 + (header_end - header_start))
    17                                  
    18                                  header_start:
    19                                  
    20                                  framebuffer_tag_start:
    21 00000010 0500                        dw 5                       ; tag type: framebuffer
    22 00000012 0100                        dw 1                       ; optional
    23 00000014 14000000                    dd framebuffer_tag_end - framebuffer_tag_start
    24 00000018 20030000                    dd 800                     ; width
    25 0000001C 58020000                    dd 600                     ; height
    26 00000020 20000000                    dd 32                      ; bpp
    27                                  framebuffer_tag_end:
    28                                  
    29 00000024 0000                        dw 0                       ; end tag
    30 00000026 0000                        dw 0
    31 00000028 08000000                    dd 8
    32                                  
    33                                  header_end:
    34                                  
    35                                  section .text
    36                                  global start
    37                                  global load_idt
    38                                  extern k_main
    39                                  
    40                                  load_idt:
    41 00000000 0F0118                      lidt [eax]
    42 00000003 C3                          ret
    43                                  
    44                                  start:
    45 00000004 FA                          cli
    46                                  
    47                                      ; multiboot2 info pointer is in [esp + 4]
    48 00000005 8B742404                    mov esi, [esp + 4]
    49                                  
    50                                  .find_fb:
    51 00000009 8B06                        mov eax, [esi]         ; tag type
    52 0000000B 83F808                      cmp eax, 8             ; type 8 = framebuffer
    53 0000000E 740D                        je .found
    54 00000010 8B4604                      mov eax, [esi + 4]     ; tag size
    55 00000013 01C6                        add esi, eax
    56 00000015 83C607                      add esi, 7
    57 00000018 83E6F8                      and esi, 0xFFFFFFF8    ; align to 8 bytes
    58 0000001B EBEC                        jmp .find_fb
    59                                  
    60                                  .found:
    61 0000001D 8B5E08                      mov ebx, [esi + 8]     ; framebuffer address
    62                                  
    63                                  ;
    64                                  ; CONTEXT:
    65                                  ; There are some things that MUST be done in Assembly, not so much because 
    66                                  ; of their difficulty (per se), but because of the "space" involved. Using "C" makes 
    67                                  ; everything heavier, but it's used because it's convenient and/or easy to understand. 
    68                                  ;So, some things are being done in ".s," especially those that require "RAM," "CPU," "GPU," etc.
    69                                  ;Although we try to avoid using ".s," some things are NECESSARY. :D
