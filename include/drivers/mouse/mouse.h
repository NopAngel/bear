#ifndef MOUSE_DRIVER_H
#define MOUSE_DRIVER_H

#define MOUSE_PORT 0x64
#define MOUSE_DATA 0x60

void mouse_write(unsigned char a);
unsigned char mouse_read();
void mouse_init();
void mouse_handler();

#endif /* MOUSE_DRIVER_H */
