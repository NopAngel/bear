#include "init.h"

int main() {
    // Inicializa subsistemas del kernel
    bearos_init_memory();
    bearos_init_drivers();
    bearos_init_interrupts();
    bearos_init_scheduler();

    // Inicia el kernel
    bearos_start_kernel();

    return 0;
}
