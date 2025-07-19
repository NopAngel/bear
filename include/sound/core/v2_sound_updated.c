
#define SOUND_COMMAND_PORT 0x388 
#define SOUND_DATA_PORT 0x389    


static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}


void sound_init() {

    outb(SOUND_COMMAND_PORT, 0x01);
   
}


void play_tone(unsigned int frequency) {


    outb(SOUND_DATA_PORT, (unsigned char)(frequency & 0xFF));      
    outb(SOUND_DATA_PORT + 1, (unsigned char)((frequency >> 8) & 0xFF)); 
}


void stop_tone() {
    // k_printf("Stopping tone...\n", 2, 0x0F); 
    outb(SOUND_COMMAND_PORT, 0x00); 
}
