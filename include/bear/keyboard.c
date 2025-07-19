#define KEYBOARD_PORT 0x60       // Puerto para leer el teclado
#define SCREEN_BUFFER ((unsigned char *)0xb8000) // Memoria de video
#define SCREEN_COLUMNS 80       // Columnas en modo texto
#define SCREEN_ROWS 25          // Filas en modo texto
#define INPUT_BUFFER_SIZE 256  


int cursor_x = 0;      // Posición horizontal del cursor
int cursor_y = 0;      // Posición vertical del cursor
char input_buffer[INPUT_BUFFER_SIZE]; // Buffer de entrada de texto
int input_index = 0;            // Índice para el buffer de entrada

// Variable para evitar múltiples lecturas del mismo scancode
volatile unsigned char last_scancode = 0;

// Lee un carácter desde el puerto del teclado
unsigned char read_scancode() {
    unsigned char scancode;
    asm volatile ("inb %1, %0" : "=a"(scancode) : "Nd"(KEYBOARD_PORT));
    return scancode;
}

// IN LANGUAGE ENGLISH
const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0F
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '´', '+', '\n', 0, // 0x10 - 0x1F
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',      // 0x20 - 0x2D
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,   // 0x2E - 0x3F
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,            // 0x40 - 0x4F
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0             // 0x50 - 0x5F
};


void put_char(char c) {
    int pos = (cursor_y * SCREEN_COLUMNS + cursor_x) * 2;

    SCREEN_BUFFER[pos] = c;          // Almacenar carácter
    SCREEN_BUFFER[pos + 1] = 0x07;  // Atributo de color (blanco)

    // Actualizamos la posición del cursor
    cursor_x++;
    if (cursor_x >= SCREEN_COLUMNS) {
        cursor_x = 0;
        cursor_y++;
    }

    // Si alcanzamos el final de la pantalla, desplazamos
    if (cursor_y >= SCREEN_ROWS) {
        scroll_screen(); // Llama a la nueva función de desplazamiento
    }
}