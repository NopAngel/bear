/*
 * BearOS - SVGA Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef SVGA_DRIVER_H
#define SVGA_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Resoluciones SVGA comunes
#define SVGA_WIDTH 1024
#define SVGA_HEIGHT 768
#define SVGA_BPP 32 // Bits por píxel (32 bits - RGBA)

// Inicializa el controlador SVGA
void svga_init();

// Establece un modo gráfico (ejemplo: 1024x768x32bpp)
uint8_t svga_set_mode(uint32_t width, uint32_t height, uint32_t bpp);

// Escribe un píxel en coordenadas (x, y) con un color ARGB
void svga_put_pixel(uint32_t x, uint32_t y, uint32_t color);

// Limpia la pantalla con un color específico
void svga_clear_screen(uint32_t color);

#endif // SVGA_DRIVER_H
