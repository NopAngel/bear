#include "sound_core.h"


uint8_t sound_memory;

int main() {
   
    sound_init(&sound_memory);

   
    sound_generate(SOUND_MID, 1000);

    if (sound_detect()) {

       
    }

    return 0;
}
