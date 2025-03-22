#include "svga_driver.h"

// Dirección base de la memoria de video (VRAM)
#define VRAM_BASE 0xA0000
#define VRAM_SIZE (1024 * 768 * 4) // Tamaño para 1024x768 con 32 bits por píxel

// Puntero a la memoria de video
static uint8_t* vram = (uint8_t*)VRAM_BASE;

// Inicializa el controlador SVGA
void svga_init() {
    // Aquí configurarías el hardware utilizando interrupciones o registros específicos de la tarjeta gráfica
    // Simulación para este ejemplo:
    vram = (uint8_t*)VRAM_BASE;
}

// Establece un modo gráfico
uint8_t svga_set_mode(uint32_t width, uint32_t height, uint32_t bpp) {
    // En un sistema real, se necesita interactuar con el hardware mediante el estándar VESA
    // Por ahora, asumimos que el modo gráfico se establece correctamente:
    if (width > SVGA_WIDTH || height > SVGA_HEIGHT || bpp != SVGA_BPP) {
        return 0; // Modo no soportado
    }
    return 1; // Modo establecido
}

// Escribe un píxel en coordenadas (x, y)
void svga_put_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x >= SVGA_WIDTH || y >= SVGA_HEIGHT) {
        return; // Coordenadas fuera de rango
    }

    uint32_t offset = (y * SVGA_WIDTH + x) * (SVGA_BPP / 8);
    vram[offset] = (color & 0xFF);         // Canal azul
    vram[offset + 1] = (color >> 8) & 0xFF; // Canal verde
    vram[offset + 2] = (color >> 16) & 0xFF; // Canal rojo
    vram[offset + 3] = (color >> 24) & 0xFF; // Canal alfa (opcional)
}

// Limpia la pantalla con un color específico
void svga_clear_screen(uint32_t color) {
    for (uint32_t y = 0; y < SVGA_HEIGHT; y++) {
        for (uint32_t x = 0; x < SVGA_WIDTH; x++) {
            svga_put_pixel(x, y, color);
        }
    }
}
