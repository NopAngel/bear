#define AUDIO_PORT 0x220
#define AUDIO_COMMAND 0x221

void headphone_write(unsigned char a) {
    while ((inportb(AUDIO_PORT) & 0x02) != 0);
    outportb(AUDIO_COMMAND, a);
}

unsigned char headphone_read() {
    while ((inportb(AUDIO_PORT) & 0x01) == 0);
    return inportb(AUDIO_COMMAND);
}

void headphone_init() {
    headphone_write(0xD0); 
    headphone_write(0xF5); 
}

void headphone_handler() {
    unsigned char volume = headphone_read();
    unsigned char balance = headphone_read();
}
