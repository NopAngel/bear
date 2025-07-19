

#ifndef SOUND_H
#define SOUND_H


static inline void outb(unsigned short port, unsigned char value) ;
void sound_init() ;
void play_tone(unsigned int frequency) ;
void stop_tone();

#endif
