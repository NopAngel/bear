#ifndef VESA_H
#define VESA_H


#define VESA_MEMORY 0xA0000
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#ifndef VESA_H
#define VESA_H

void set_vesa_mode();
void draw_pixel(int x, int y, short color);
void draw_horizontal_line(int y, int x_start, int x_end, short color);
void draw_vertical_line(int x, int y_start, int y_end, short color);
void draw_rectangle(int x, int y, int width, int height, short color);

#endif


#endif
