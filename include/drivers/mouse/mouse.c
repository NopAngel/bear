#define MOUSE_PORT 0x64
#define MOUSE_DATA 0x60

static inline unsigned char inportb(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline void outportb(unsigned short port, unsigned char value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

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
