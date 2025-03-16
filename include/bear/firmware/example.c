#include "firmware.h"

int main() {
    // Inicializa el firmware
    firmware_init();

    // Realiza los diagnósticos
    firmware_diagnostic();

    // Aquí continuaría el loop del kernel o sistema principal
    while (1) {
        // Loop infinito
    }

    return 0;
}
