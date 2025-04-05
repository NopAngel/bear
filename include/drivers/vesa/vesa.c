#define VESA_MEMORY 0xA0000
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Cambiar al modo gráfico VESA
void set_vesa_mode() {
    asm volatile (
        "mov $0x4F02, %%ax\n"  // Función VESA para cambiar el modo
        "mov $0x118, %%bx\n"   // Modo gráfico: 800x600, 16 bits por píxel
        "int $0x10\n"          // Interrupción de BIOS
        :
        : /* Sin parámetros */
        : "eax", "ebx"
    );
}

// Dibujar un píxel en (x, y) con el color especificado
void draw_pixel(int x, int y, short color) {
    short *vesa = (short *)VESA_MEMORY;
    int offset = y * SCREEN_WIDTH + x;  // Calcula el índice del píxel
    vesa[offset] = color;
}

// Dibujar una línea horizontal
void draw_horizontal_line(int y, int x_start, int x_end, short color) {
    for (int x = x_start; x <= x_end; x++) {
        draw_pixel(x, y, color);
    }
}

// Dibujar una línea vertical
void draw_vertical_line(int x, int y_start, int y_end, short color) {
    for (int y = y_start; y <= y_end; y++) {
        draw_pixel(x, y, color);
    }
}

// Dibujar un rectángulo
void draw_rectangle(int x, int y, int width, int height, short color) {
    for (int i = 0; i < height; i++) {
        draw_horizontal_line(y + i, x, x + width - 1, color);
    }
}

// Función principal del kernel
void kernel_main() {
    set_vesa_mode();  // Configura el modo gráfico VESA

    // Dibujar gráficos básicos
    draw_pixel(400, 300, 0xFFFF);  // Píxel blanco en el centro de la pantalla
    draw_rectangle(100, 100, 200, 150, 0x07E0);  // Rectángulo verde
    draw_horizontal_line(300, 100, 700, 0xF800); // Línea horizontal roja
    draw_vertical_line(400, 100, 500, 0x001F);   // Línea vertical azul

    while (1) {}  // Evitar que el kernel termine
}
