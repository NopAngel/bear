#ifndef SOUNDWIRE_H
#define SOUNDWIRE_H

#define SOUNDWIRE_BASE_ADDR 0xFE000000

typedef struct {
    unsigned int base_addr;
    unsigned int irq;
    unsigned int clock_freq;
    int initialized;
} SoundWireDevice;

void soundwire_init();
void soundwire_setup();
void soundwire_play_tone(unsigned int freq, unsigned int duration);
unsigned int soundwire_read_reg(unsigned int reg);
void soundwire_write_reg(unsigned int reg, unsigned int value);

#endif