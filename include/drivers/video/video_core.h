/*
 * BearOS - Video Core Header
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef VIDEO_CORE_H
#define VIDEO_CORE_H

// Define tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Dimensiones de la pantalla en modo texto VGA
#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25

// Colores para texto
#define VIDEO_COLOR_BLACK 0x0
#define VIDEO_COLOR_WHITE 0xF
#define VIDEO_COLOR_RED   0x4
#define VIDEO_COLOR_GREEN 0x2
#define VIDEO_COLOR_BLUE  0x1

// Inicializa el núcleo de video
void video_init();

// Escribe un carácter en una posición específica
void video_put_char(uint8_t character, uint32_t x, uint32_t y, uint8_t color);

// Escribe una cadena de texto en una posición específica
void video_write_text(const char* text, uint32_t x, uint32_t y, uint8_t color);

// Limpia la pantalla con un color específico
void video_clear(uint8_t color);

#endif // VIDEO_CORE_H
