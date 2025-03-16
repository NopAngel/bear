#include "gpu_driver.h"
#include "bear/k_print.h" // Para mostrar mensajes en el sistema

// Simulación de framebuffer en memoria (VRAM)
static uint32_t framebuffer[GPU_SCREEN_WIDTH * GPU_SCREEN_HEIGHT];

// Inicializa la GPU
void gpu_init() {
    gpu_clear_screen(0x000000); // Limpia la pantalla (color negro)
    k_printf("Controlador de GPU inicializado.\n", 10, 0x0A); // Línea 10, verde
}

// Dibuja un píxel en una posición específica
void gpu_draw_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x >= GPU_SCREEN_WIDTH || y >= GPU_SCREEN_HEIGHT) {
        return; // Fuera de los límites de la pantalla
    }

    uint32_t index = y * GPU_SCREEN_WIDTH + x; // Calcula la posición en el framebuffer
    framebuffer[index] = color;
}

// Limpia la pantalla con un color específico
void gpu_clear_screen(uint32_t color) {
    for (uint32_t y = 0; y < GPU_SCREEN_HEIGHT; y++) {
        for (uint32_t x = 0; x < GPU_SCREEN_WIDTH; x++) {
            gpu_draw_pixel(x, y, color);
        }
    }
}

// Dibuja un rectángulo sólido
void gpu_draw_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
    for (uint32_t j = 0; j < height; j++) {
        for (uint32_t i = 0; i < width; i++) {
            gpu_draw_pixel(x + i, y + j, color);
        }
    }
}
