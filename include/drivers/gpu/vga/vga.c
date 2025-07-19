// Dirección base de la memoria de video VGA en modo texto
#define VGA_MEMORY (char *)0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Colores de texto y fondo (valores VGA)
#define COLOR_WHITE 0x0F
#define COLOR_RED 0x04
#define COLOR_GREEN 0x02
#define COLOR_BLUE 0x01

// Variable para rastrear la posición actual del cursor
static int cursor_x = 0;
static int cursor_y = 0;

// Prototipos de funciones
void vga_clear_screen(uint8_t color);
void vga_put_char(char c, uint8_t color);
void vga_put_string(const char *str, uint8_t color);
void vga_set_cursor(int x, int y);

// Función para limpiar la pantalla
void vga_clear_screen(uint8_t color) {
    char *vga_buffer = VGA_MEMORY;
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            int index = (y * VGA_WIDTH + x) * 2;
            vga_buffer[index] = ' ';        // Espacio en blanco
            vga_buffer[index + 1] = color; // Color
        }
    }
    cursor_x = 0;
    cursor_y = 0;
    vga_set_cursor(cursor_x, cursor_y);
}

// Función para escribir un carácter en la posición actual del cursor
void vga_put_char(char c, uint8_t color) {
    if (c == '\n') { // Salto de línea
        cursor_x = 0;
        cursor_y++;
    } else {
        char *vga_buffer = VGA_MEMORY;
        int index = (cursor_y * VGA_WIDTH + cursor_x) * 2;
        vga_buffer[index] = c;      // Carácter
        vga_buffer[index + 1] = color; // Color
        cursor_x++;
    }

    // Manejar el desplazamiento si se supera el límite de pantalla
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    if (cursor_y >= VGA_HEIGHT) {
        vga_clear_screen(COLOR_WHITE); // Limpia la pantalla si se llena
        cursor_y = 0;
    }

    vga_set_cursor(cursor_x, cursor_y);
}

// Función para escribir una cadena de texto
void vga_put_string(const char *str, uint8_t color) {
    while (*str) {
        vga_put_char(*str++, color);
    }
}

// Función para configurar la posición del cursor
void vga_set_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;
    // Enviar posición al puerto VGA
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
