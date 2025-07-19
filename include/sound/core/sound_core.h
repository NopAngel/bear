
/*
*
*   sound_core.h - core for the sound
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/

#ifndef SOUND_CORE_H
#define SOUND_CORE_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;


#define SOUND_LOW 261  
#define SOUND_MID 440  
#define SOUND_HIGH 880  


void sound_init(uint8_t* sound_memory);


void sound_generate(uint32_t frequency, uint32_t duration_ms);


uint8_t sound_detect();

#endif
