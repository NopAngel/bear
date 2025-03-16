/*
 * BearOS - GPU Driver Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef GPU_DRIVER_H
#define GPU_DRIVER_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Tamaños y configuraciones gráficas
#define GPU_SCREEN_WIDTH  1024
#define GPU_SCREEN_HEIGHT 768
#define GPU_BPP           32 // Bits por píxel (RGBA)

// Inicializa la GPU
void gpu_init();

// Dibuja un píxel en una posición específica
void gpu_draw_pixel(uint32_t x, uint32_t y, uint32_t color);

// Limpia la pantalla con un color específico
void gpu_clear_screen(uint32_t color);

// Dibuja un rectángulo sólido
void gpu_draw_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color);

#endif // GPU_DRIVER_H
