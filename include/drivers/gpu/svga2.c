#define SVGA_IO_BASE       0x00001100  
#define SVGA_INDEX_PORT    SVGA_IO_BASE + 0
#define SVGA_VALUE_PORT    SVGA_IO_BASE + 1


#define SVGA_REG_ID        0
#define SVGA_REG_ENABLE    1
#define SVGA_REG_WIDTH     2
#define SVGA_REG_HEIGHT    3
#define SVGA_REG_BITS_PER_PIXEL  4
#define SVGA_REG_FB_START  13
#define SVGA_REG_FB_SIZE   14


#define SVGA_ID_2          0x90000002



static inline void svga_write_register(unsigned int index, unsigned int value) {
    outl(index, SVGA_INDEX_PORT);
    outl(value, SVGA_VALUE_PORT);
}

static inline unsigned int svga_read_register(unsigned int index) {
    outl(index, SVGA_INDEX_PORT);
    return inl(SVGA_VALUE_PORT);
}



void svga_init(unsigned int width, unsigned int height, unsigned int bpp) {
    if (svga_read_register(SVGA_REG_ID) != SVGA_ID_2) {
        // Error: not found
        return;
    }

    svga_write_register(SVGA_REG_ENABLE, 0);
    svga_write_register(SVGA_REG_WIDTH, width);
    svga_write_register(SVGA_REG_HEIGHT, height);
    svga_write_register(SVGA_REG_BITS_PER_PIXEL, bpp);
    svga_write_register(SVGA_REG_ENABLE, 1);
}



volatile unsigned char* framebuffer;

void svga_map_framebuffer() {
    unsigned int fb_start = svga_read_register(SVGA_REG_FB_START);
    framebuffer = (volatile unsigned char*)fb_start;
}



void svga_draw_pixel(int x, int y, unsigned int color, int width) {
    int offset = (y * width + x) * 4;
    *((unsigned int*)(framebuffer + offset)) = color;
}




void driver_entry() {
    svga_init(800, 600, 32);
    svga_map_framebuffer();

    // Screen clean black
    for (int y = 0; y < 600; y++) {
        for (int x = 0; x < 800; x++) {
            svga_draw_pixel(x, y, 0x000000, 800);
        }
    }

    // Line RED
    for (int x = 100; x < 700; x++) {
        svga_draw_pixel(x, 300, 0xFF0000, 800);
    }
}
