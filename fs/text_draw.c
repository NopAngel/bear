#define VIDEO_MEMORY ((unsigned short*)0xB8000)
#define SCREEN_WIDTH 80

void text_draw(int x, int y, char c, unsigned char color) {
    unsigned short attribute = ((unsigned short)color << 8) | c;
    VIDEO_MEMORY[y * SCREEN_WIDTH + x] = attribute;
}
