#include "video_core.h"

int main() {
    // Inicializa el núcleo de video
    video_init();

    // Escribe mensajes en la pantalla
    video_write_text("Bienvenido a BearOS!\n", 0, 0, VIDEO_COLOR_WHITE);
    video_write_text("Inicializando subsistemas...\n", 0, 1, VIDEO_COLOR_GREEN);
    video_write_text("Listo para recibir comandos.\n", 0, 2, VIDEO_COLOR_BLUE);

    // Mantén el sistema en un loop infinito
    while (1) {
        // Tu loop principal del kernel aquí
    }

    return 0;
}
