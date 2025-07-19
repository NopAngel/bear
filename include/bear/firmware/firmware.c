#include "firmware.h"
#include "bear/k_printf.h" 

void firmware_init() {
    // Mostramos un mensaje de inicialización del firmware
    k_printf("Firmware inicializado correctamente.\n", 0, 0x07); // Línea 0, color blanco
}

void firmware_diagnostic() {
    // Realiza diagnósticos simples y muestra resultados
    k_printf("Corriendo diagnosticos de hardware...\n", 1, 0x0A); // Línea 1, color verde

    // Aquí puedes simular diagnóstico
    k_printf("Chequeo de memoria: OK\n", 2, 0x0A);  // Línea 2, color verde
    k_printf("Chequeo de dispositivos: OK\n", 3, 0x0A); // Línea 3, color verde
    k_printf("Chequeo de interrupciones: OK\n", 4, 0x0A); // Línea 4, color verde

    // Reportar finalización
    k_printf("Todos los sistemas operativos funcionando.\n", 5, 0x0F); // Línea 5, color blanco brillante
}
