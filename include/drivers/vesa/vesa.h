#ifndef VESA_H
#define VESA_H

// Dirección base típica de la memoria gráfica VESA
#define VESA_MEMORY 0xA0000
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Función para cambiar al modo gráfico VESA
void set_vesa_mode();

// Función para dibujar un píxel en (x, y)
void draw_pixel(int x, int y, short color);

// Función para dibujar una línea horizontal
void draw_horizontal_line(int y, int x_start, int x_end, short color);

// Función para dibujar una línea vertical
void draw_vertical_line(int x, int y_start, int y_end, short color);

// Función para dibujar un rectángulo
void draw_rectangle(int x, int y, int width, int height, short color);

#endif
