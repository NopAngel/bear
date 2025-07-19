#ifndef HEADPHONE_DRIVER_H
#define HEADPHONE_DRIVER_H

#define AUDIO_PORT 0x220
#define AUDIO_COMMAND 0x221

void headphone_write(unsigned char a);
unsigned char headphone_read();
void headphone_init();
void headphone_handler();

#endif /* HEADPHONE_DRIVER_H */
