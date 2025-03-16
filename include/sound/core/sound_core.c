a.c#include "sound_core.h"

// Memoria que simula el registro de control del dispositivo de sonido
static uint8_t* sound_register = (void*)0;

// Inicializa el núcleo de sonido
void sound_init(uint8_t* sound_memory) {
    sound_register = sound_memory;
    *sound_register = 0; // El sistema de sonido comienza "en silencio"
}

// Genera un sonido con una frecuencia y duración especificadas
void sound_generate(uint32_t frequency, uint32_t duration_ms) {
    if (sound_register == (void*)0) return;

    // Convertimos la frecuencia en un patrón de bits "encendido/apagado"
    uint32_t cycles = (frequency * duration_ms) / 1000; // Calcula ciclos de onda

    for (uint32_t i = 0; i < cycles; i++) {
        *sound_register = 1; // "Encender" la onda
        // Simula un pequeño delay (sin usar funciones estándar)
        for (volatile uint32_t j = 0; j < 1000; j++) {}

        *sound_register = 0; // "Apagar" la onda
        for (volatile uint32_t j = 0; j < 1000; j++) {}
    }
}

// Detecta un cambio de estado en los bits simulados (como entrada de sonido)
uint8_t sound_detect() {
    if (sound_register == (void*)0) return 0;

    // Detecta si el estado del registro cambió (ej. sonido externo)
    static uint8_t previous_state = 0;
    uint8_t current_state = *sound_register;

    if (current_state != previous_state) {
        previous_state = current_state;
        return 1; // Detecta un cambio
    }

    return 0; // No hubo cambios
}
