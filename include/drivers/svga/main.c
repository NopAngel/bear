#include "svga_driver.h"

int main() {
    // Inicializa el controlador SVGA
    svga_init();

    // Establece el modo gráfico 1024x768x32bpp
    if (!svga_set_mode(SVGA_WIDTH, SVGA_HEIGHT, SVGA_BPP)) {
        // Si no se puede establecer el modo gráfico, detén el sistema
        return -1;
    }

    // Limpia la pantalla con un color azul
    svga_clear_screen(0xFF0000FF); // Color ARGB: azul

    // Dibuja un píxel rojo en el centro de la pantalla
    svga_put_pixel(SVGA_WIDTH / 2, SVGA_HEIGHT / 2, 0xFFFF0000); // Color ARGB: rojo

    // Loop infinito
    while (1) {}

    return 0;
}
