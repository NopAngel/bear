void shutdown_system() {
    // Deshabilitar las interrupciones
    __asm__ volatile("cli");

    // Solicitar el apagado a través de la BIOS usando APM
    __asm__ volatile (
        "mov $0x5307, %ax\n"  // Función APM: APAGADO
        "mov $0x0001, %bx\n"  // Solicitud para apagar el sistema
        "mov $0x0003, %cx\n"  // Estado del dispositivo: Apagar
        "int $0x15\n"         // Llamada a la interrupción de APM
    );

    // Si el apagado falla, permanecer en un bucle infinito
    while (1);
}

/* how to use???? 

    __asm__ volatile (
        "mov $0x13, %ax\n"  // Modo VGA 13h
        "int $0x10\n"       // Interrupción del BIOS
    );

    // Simular un mensaje antes del apagado
    k_printf("Apagando el sistema en 5 segundos...", 0, RED_TXT);

    // Esperar un tiempo antes de apagar (simulada con un bucle)
    for (volatile int i = 0; i < 50000000; i++) { }

    // Llamar a la función de apagado
    shutdown_system();



*/