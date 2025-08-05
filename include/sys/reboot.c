

void reboot_system() {
    // Deshabilitamos las interrupciones
    __asm__ volatile("cli");

    // Esperar que el buffer de salida del controlador esté vacío
    while (1) {
        unsigned char status;
        __asm__ volatile (
            "inb %1, %0"            // Leer el estado del puerto 0x64
            : "=a"(status)          // El resultado se almacena en "status"
            : "Nd"(0x64)            // Puerto de E/S 0x64
        );
        if ((status & 0x02) == 0) { // Verificar si el bit ocupado está en 0
            break;
        }
    }

    // Enviar el comando de reinicio al puerto 0x64
    __asm__ volatile (
        "outb %0, %1"              // Enviar un comando al puerto
        :                          // No hay salida
        : "a"((unsigned char)0xFE), "Nd"(0x64)  // Valor inmediato en %al, puerto 0x64
    );

    // Si el reinicio falla, mantener un bucle infinito
    while (1);
}
