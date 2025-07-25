#ifndef TEXTDRAW_H
#define TEXTDRAW_H

#define VIDEO_MEMORY ((unsigned short*)0xB8000)
#define SCREEN_WIDTH 80

void text_draw(int x, int y, char c, unsigned char color);

#endif // TEXTDRAW_H