#pragma once

// Tipos básicos
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// Puertos I/O del teclado PS/2
#define PS2_DATA    0x60
#define PS2_STATUS  0x64

// Tamaño del búfer circular de entrada
#define KEYBUF_SIZE 128

// Funciones públicas
u8  inb123(u16 port);
void outb123(u16 port, u8 val);

void ps2_init();             // Inicialización (por ahora vacío)
void ps2_loop();             // Bucle principal de lectura del teclado

void ps2_buffer_push(u8 scancode); // Agrega al búfer
int  ps2_buffer_pop();             // Extrae scancode (-1 si vacío)
int  ps2_data_ready();            // ¿Hay dato listo en el puerto?
