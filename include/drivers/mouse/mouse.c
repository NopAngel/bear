#define MOUSE_PORT 0x64
#define MOUSE_DATA 0x60

void mouse_write(unsigned char a) {
    while ((inportb(MOUSE_PORT) & 0x02) != 0);
    outportb(MOUSE_DATA, a);
}

unsigned char mouse_read() {
    while ((inportb(MOUSE_PORT) & 0x01) == 0);
    return inportb(MOUSE_DATA);
}

void mouse_init() {
    unsigned char status;
    mouse_write(0xA8);
    mouse_write(0x20);
    status = mouse_read() | 2;
    mouse_write(0x60);
    mouse_write(status);
    mouse_write(0xD4);
    mouse_write(0xF4);
    mouse_read();
}

void mouse_handler() {
    unsigned char state = mouse_read();
    unsigned char dx = mouse_read();
    unsigned char dy = mouse_read();
}
