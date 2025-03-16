#include "gpu_driver.h"

int main() {
    // Inicializa el controlador de GPU
    gpu_init();

    // Dibuja un rectángulo azul en el centro de la pantalla
    gpu_draw_rect(412, 334, 200, 100, 0xFF0000FF); // ARGB: azul

    // Limpia la pantalla después de 5 segundos (simulado con un loop)
    for (volatile uint32_t i = 0; i < 500000000; i++) {}
    gpu_clear_screen(0xFF000000); // ARGB: negro

    return 0;
}
