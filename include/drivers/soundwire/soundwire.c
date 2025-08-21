// soundwire.c
#include "soundwire.h"
#include "../../../fs/k_printf.h"
int soundwire_cursory;

SoundWireDevice soundwire_dev;

static inline void outb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline unsigned char inb(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline void outl(unsigned short port, unsigned int value) {
    asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

static inline unsigned int inl(unsigned short port) {
    unsigned int value;
    asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

unsigned int soundwire_read_reg(unsigned int reg) {
    if (!soundwire_dev.initialized) return 0;
    return *((volatile unsigned int*)(soundwire_dev.base_addr + reg));
}

void soundwire_write_reg(unsigned int reg, unsigned int value) {
    if (!soundwire_dev.initialized) return;
    *((volatile unsigned int*)(soundwire_dev.base_addr + reg)) = value;
}

void soundwire_init() {
    soundwire_dev.base_addr = SOUNDWIRE_BASE_ADDR;
    soundwire_dev.initialized = 1;
    
    k_printf("SoundWire initialized at 0x", soundwire_cursory++, 0x0F);
    char addr_str[16];
    itoa(SOUNDWIRE_BASE_ADDR, addr_str, 16);
    k_printf(addr_str, soundwire_cursory++, 0x0F);
}

void soundwire_setup() {
    if (!soundwire_dev.initialized) return;
    
    soundwire_write_reg(0x00, 0x1);
    for (int i = 0; i < 1000; i++) asm volatile("nop");
    
    soundwire_write_reg(0x08, 48000);
    soundwire_write_reg(0x0C, 0x1F);
    soundwire_write_reg(0x00, 0x3);
    
    k_printf("SoundWire configured", soundwire_cursory++, 0x0A);
}

void soundwire_play_tone(unsigned int freq, unsigned int duration) {
    if (!soundwire_dev.initialized) return;
    
    for (unsigned int i = 0; i < duration * 1000; i++) {
        unsigned int sample = (i % freq) * 100;
        soundwire_write_reg(0x14, sample);
        
        for (int j = 0; j < 100; j++) asm volatile("nop");
    }
    
    soundwire_write_reg(0x14, 0);
}

void soundwire_beep() {
    soundwire_play_tone(440, 1);
}

void soundwire_test() {
    soundwire_init();
    soundwire_setup();
    
    k_printf("Playing test sounds...", soundwire_cursory++, 0x0E);
    
    soundwire_play_tone(262, 1);
    soundwire_play_tone(294, 1);
    soundwire_play_tone(330, 1);
    soundwire_play_tone(349, 1);
    soundwire_play_tone(392, 1);
    soundwire_play_tone(440, 1);
    soundwire_play_tone(494, 1);
    
    k_printf("Sound test complete!", soundwire_cursory++, 0x0A);
}
