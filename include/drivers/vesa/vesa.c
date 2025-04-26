#define VESA_MEMORY 0xA0000
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void set_vesa_mode() {
    asm volatile (
        "mov $0x4F02, %%ax\n"  // function VESA
        "mov $0x118, %%bx\n"   // Mode graphics: 800x600, 16 bits for pixel
        "int $0x10\n"          // INTERUPTION Of the BIOS
        :
        : 
        : "eax", "ebx"
    );
}


void draw_pixel(int x, int y, short color) {
    short *vesa = (short *)VESA_MEMORY;
    int offset = y * SCREEN_WIDTH + x;  
    vesa[offset] = color;
}


void draw_horizontal_line(int y, int x_start, int x_end, short color) {
    for (int x = x_start; x <= x_end; x++) {
        draw_pixel(x, y, color);
    }
}


void draw_vertical_line(int x, int y_start, int y_end, short color) {
    for (int y = y_start; y <= y_end; y++) {
        draw_pixel(x, y, color);
    }
}

void draw_rectangle(int x, int y, int width, int height, short color) {
    for (int i = 0; i < height; i++) {
        draw_horizontal_line(y + i, x, x + width - 1, color);
    }
}
/*
void kernel_main() {
    set_vesa_mode(); 

    draw_pixel(400, 300, 0xFFFF);  
    draw_rectangle(100, 100, 200, 150, 0x07E0); 
    draw_horizontal_line(300, 100, 700, 0xF800);
    draw_vertical_line(400, 100, 500, 0x001F);   

    while (1) {}  
}
*/