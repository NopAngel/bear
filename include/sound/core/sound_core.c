
/*
*
*   sound_core.c - core for the sound
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/

#include "sound_core.h"


static uint8_t* sound_register = (void*)0;


void sound_init(uint8_t* sound_memory) {
    sound_register = sound_memory;
    *sound_register = 0; 
}


void sound_generate(uint32_t frequency, uint32_t duration_ms) {
    if (sound_register == (void*)0) return;


    uint32_t cycles = (frequency * duration_ms) / 1000; 

    for (uint32_t i = 0; i < cycles; i++) {
        *sound_register = 1; 
        for (volatile uint32_t j = 0; j < 1000; j++) {}

        *sound_register = 0; 
        for (volatile uint32_t j = 0; j < 1000; j++) {}
    }
}


uint8_t sound_detect() {
    if (sound_register == (void*)0) return 0;

    static uint8_t previous_state = 0;
    uint8_t current_state = *sound_register;

    if (current_state != previous_state) {
        previous_state = current_state;
        return 1; 
    }

    return 0; 
}
