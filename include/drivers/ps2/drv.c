typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// Puertos de PS/2
#define PS2_DATA    0x60
#define PS2_STATUS  0x64

// I/O: lectura y escritura de puertos
u8 inb123(u16 port) {
    u8 ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb123(u16 port, u8 val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Verifica si hay datos disponibles en el buffer del PS/2
int ps2_data_ready() {
    return inb123(PS2_STATUS) & 1;
}

// Búfer circular de entrada de teclas (scancodes)
#define KEYBUF_SIZE 128
u8 key_buffer[KEYBUF_SIZE];
int key_head = 0;
int key_tail = 0;

// Agrega scancode al búfer
void ps2_buffer_push(u8 scancode) {
    int next = (key_head + 1) % KEYBUF_SIZE;
    if (next != key_tail) {
        key_buffer[key_head] = scancode;
        key_head = next;
    }
}

// Extrae scancode (si hay)
int ps2_buffer_pop() {
    if (key_head == key_tail) return -1; // vacío
    u8 val = key_buffer[key_tail];
    key_tail = (key_tail + 1) % KEYBUF_SIZE;
    return val;
}

// Inicializa driver (si es necesario)
void ps2_init() {
    // Por ahora vacío, pero aquí podrías enviar comandos a 0x64 para configurar
}

// Bucle de captura: leer scancodes e ingresarlos al búfer
void ps2_loop() {
    while (1) {
        if (ps2_data_ready()) {
            u8 scancode = inb123(PS2_DATA);
            ps2_buffer_push(scancode);
        }
    }
}
