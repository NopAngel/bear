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

/*HOW TO USE? 
else if (strcmp(input_buffer, "reboot") == 0) {

        __asm__ volatile (
        "mov $0x13, %ax\n"  // Modo VGA 13h
        "int $0x10\n"       // Interrupción del BIOS
    );

    // Simular algún escenario crítico y luego reiniciar
    k_printf("Reiniciando el sistema en 5 segundos...", 1, RED_TXT);

    // Esperar (simulada, por simplicidad)
    for (volatile int i = 0; i < 50000000; i++) { }

    reboot_system();    
    }*/