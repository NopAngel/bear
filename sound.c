
#define SOUND_COMMAND_PORT 0x388  // Ejemplo de puerto base del hardware de sonido
#define SOUND_DATA_PORT 0x389    // Puerto para datos

// Función para escribir en un puerto (hardware directo)
static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Función para inicializar el hardware de sonido
void sound_init() {
    // Enviar un comando de inicialización al hardware
    outb(SOUND_COMMAND_PORT, 0x01); // Ejemplo de comando
    // Usando tu función para mensajes k_printf("Sonido inicializado.\n", 0, 0x0F); 
}

// Función para reproducir un tono
void play_tone(unsigned int frequency) {
   // Feedback al usuario del kernel  k_printf("Reproduciendo tono...\n", 1, 0x0F); 

    // Configurar la frecuencia del sonido
    outb(SOUND_DATA_PORT, (unsigned char)(frequency & 0xFF));       // Parte baja
    outb(SOUND_DATA_PORT + 1, (unsigned char)((frequency >> 8) & 0xFF)); // Parte alta
}

// Función para detener el sonido
void stop_tone() {
    // k_printf("Deteniendo tono...\n", 2, 0x0F); 
    outb(SOUND_COMMAND_PORT, 0x00); // Enviar comando de detener
}
