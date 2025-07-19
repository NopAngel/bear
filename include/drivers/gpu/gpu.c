


#define VIDEO_MEMORY 0xA0000 // Dirección base de memoria VGA
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

// Función para configurar el modo de video VGA (320x200x256 colores)
void set_video_mode() {
    // Usamos la interrupción del BIOS 0x10 para cambiar al modo 0x13
    __asm__ volatile (
        "mov $0x13, %ax\n"  // Establecer modo 0x13
        "int $0x10\n"       // Interrupción BIOS para video
    );
}

// Función para dibujar un píxel directamente en la memoria de video
void draw_pixel_gpu(int x, int y, unsigned char color) {
    char *video = (char *)VIDEO_MEMORY; // Puntero a memoria VGA
    video[(y * SCREEN_WIDTH) + x] = color; // Escribir en la posición adecuada
}

// Función para rellenar la pantalla con un color
void fill_screen(unsigned char color) {
    char *video = (char *)VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video[i] = color; // Llenar cada byte de memoria con el color dado
    }
}