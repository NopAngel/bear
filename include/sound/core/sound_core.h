#ifndef SOUND_CORE_H
#define SOUND_CORE_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Define las frecuencias básicas (en Hz) para los tonos
#define SOUND_LOW 261   // Frecuencia baja (ej. C4)
#define SOUND_MID 440   // Frecuencia media (ej. A4)
#define SOUND_HIGH 880  // Frecuencia alta (ej. A5)

// Inicializa el núcleo de sonido
void sound_init(uint8_t* sound_memory);

// Genera un sonido dado en bits (representando una frecuencia simple)
void sound_generate(uint32_t frequency, uint32_t duration_ms);

// Detecta cambios en los bits del sistema para simular sonido de entrada
uint8_t sound_detect();

#endif
