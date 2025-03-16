#include "video_core.h"

// Dirección base de la memoria de video
#define VIDEO_MEMORY 0xB8000

// Puntero al área de memoria de video
static uint8_t* video_mem = (uint8_t*)VIDEO_MEMORY;

// Inicializa el núcleo de video
void video_init() {
    video_clear(VIDEO_COLOR_BLACK); // Limpia la pantalla al inicio
}

// Escribe un carácter en una posición específica
void video_put_char(uint8_t character, uint32_t x, uint32_t y, uint8_t color) {
    if (x >= VIDEO_WIDTH || y >= VIDEO_HEIGHT) return; // Verifica los límites

    uint32_t index = (y * VIDEO_WIDTH + x) * 2; // Calcula la posición en la memoria
    video_mem[index] = character;              // Escribe el carácter
    video_mem[index + 1] = color;              // Escribe el color
}

// Escribe una cadena de texto en una posición específica
void video_write_text(const char* text, uint32_t x, uint32_t y, uint8_t color) {
    uint32_t offset = x;

    while (*text != '\0') {
        if (*text == '\n') { // Maneja saltos de línea
            y++;
            offset = 0;
        } else {
            video_put_char(*text, offset, y, color);
            offset++;
            if (offset >= VIDEO_WIDTH) { // Salta a la siguiente línea si se desborda
                y++;
                offset = 0;
            }
        }
        text++;
    }
}

// Limpia la pantalla con un color específico
void video_clear(uint8_t color) {
    for (uint32_t y = 0; y < VIDEO_HEIGHT; y++) {
        for (uint32_t x = 0; x < VIDEO_WIDTH; x++) {
            video_put_char(' ', x, y, color); // Rellena con espacios
        }
    }
}
