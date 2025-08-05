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
