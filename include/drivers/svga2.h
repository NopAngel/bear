#ifndef SVGA2_H
#define SVGA2_H

// Dirección base de los puertos SVGA II (VMware)
#define SVGA_IO_BASE             0x00001100
#define SVGA_INDEX_PORT          (SVGA_IO_BASE + 0)
#define SVGA_VALUE_PORT          (SVGA_IO_BASE + 1)

// Registros SVGA
#define SVGA_REG_ID              0
#define SVGA_REG_ENABLE          1
#define SVGA_REG_WIDTH           2
#define SVGA_REG_HEIGHT          3
#define SVGA_REG_BITS_PER_PIXEL  4
#define SVGA_REG_FB_START        13
#define SVGA_REG_FB_SIZE         14


#define SVGA_ID_2                0x90000002

void svga_init(unsigned int width, unsigned int height, unsigned int bpp);
void svga_map_framebuffer();
void svga_draw_pixel(int x, int y, unsigned int color, int width);


static inline void svga_write_register(unsigned int index, unsigned int value) {
    outl(index, SVGA_INDEX_PORT);
    outl(value, SVGA_VALUE_PORT);
}

static inline unsigned int svga_read_register(unsigned int index) {
    outl(index, SVGA_INDEX_PORT);
    return inl(SVGA_VALUE_PORT);
}


extern volatile unsigned char* framebuffer;

#endif 
