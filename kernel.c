
/*
				B - E - A - R      OS

						LICENSE: APACHE 2.0
						Author: NopAngel
						Repository: NopAngel

           - What you're seeing is the (main) code that makes the kernel work.
                (Libraries and similar things are also imported from the project.)

             This project is for funny purposes only and has its own commercial license.
                        Thanks for watching! :)


     @Copyright 2024-2025 - BearOS 
*/


 // Tamaño máximo del buffer de entrada
void k_clear_screen();
unsigned int k_printf(char *message, unsigned int line, unsigned int color);
unsigned int k_printf_no_newline(const char *message, unsigned int line, unsigned int color);
unsigned int k_printf_center(char *message, unsigned int line, unsigned int color);
void isr0_handler();

void free_shared_memory(void *address);
void init_shared_memory();



// SHARED MEMORY'S







void *allocate_shared_memory(unsigned int size);
void free_shared_memory(void *address);
void init_shared_memory();

// Variables globales para memoria compartida
#define SHARED_MEMORY_SIZE 4096   // Tamaño total de la memoria compartida
#define MAX_SHARED_BLOCKS 8      // Número máximo de bloques de memoria compartida

typedef struct {
    int is_used;               // Indica si el bloque está en uso
    void *start_address;       // Dirección base del bloque
    unsigned int size;         // Tamaño del bloque
} shared_block_t;

// Tabla de bloques y dirección base de memoria compartida
shared_block_t shared_blocks[MAX_SHARED_BLOCKS];
void *shared_memory_base = (void *)0x100000;

// Función para inicializar los bloques de memoria compartida
void init_shared_memory() {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        shared_blocks[i].is_used = 0;
        shared_blocks[i].start_address = shared_memory_base + (i * (SHARED_MEMORY_SIZE / MAX_SHARED_BLOCKS));
        shared_blocks[i].size = SHARED_MEMORY_SIZE / MAX_SHARED_BLOCKS;
    }
}

// Función para asignar un bloque de memoria compartida
void *allocate_shared_memory(unsigned int size) {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        if (!shared_blocks[i].is_used && shared_blocks[i].size >= size) {
            shared_blocks[i].is_used = 1; // Marcar el bloque como usado
            return shared_blocks[i].start_address; // Retornar la dirección base del bloque
        }
    }
    return 0; // Devuelve 0 si no hay bloques disponibles
}

// Función para liberar un bloque de memoria compartida
void free_shared_memory(void *address) {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        if (shared_blocks[i].start_address == address) {
            shared_blocks[i].is_used = 0; // Marcar el bloque como libre
            return;
        }
    }
}



/*
void kernel_main() {
    // Inicializar la memoria compartida
    init_shared_memory();

    // Proceso 1: Reservar un bloque de memoria compartida
    void *block1 = allocate_shared_memory(512);
    if (block1) {
        k_printf("Proceso 1 reservó memoria en: 0x%x\n", (unsigned int)block1);
    }

    // Proceso 2: Reservar otro bloque
    void *block2 = allocate_shared_memory(512);
    if (block2) {
        k_printf("Proceso 2 reservó memoria en: 0x%x\n", (unsigned int)block2);
    }

    // Proceso 1: Liberar el bloque
    free_shared_memory(block1);
    k_printf("Proceso 1 liberó su bloque\n");

    // Reasignación
    void *block3 = allocate_shared_memory(512);
    if (block3) {
        k_printf("Bloque reasignado a otro proceso: 0x%x\n", (unsigned int)block3);
    }

    while (1); // Mantener el kernel activo
}

CANT USE:

*/




// REBOOT AND APM SYSTEM


void reboot_system() {
    // Deshabilitamos las interrupciones
    __asm__ volatile("cli");

    // Esperar que el buffer de salida del controlador esté vacío
    while (1) {
        unsigned char status;
        __asm__ volatile (
            "inb %1, %0"            // Leer el estado del puerto 0x64
            : "=a"(status)          // El resultado se almacena en "status"
            : "Nd"(0x64)            // Puerto de E/S 0x64
        );
        if ((status & 0x02) == 0) { // Verificar si el bit ocupado está en 0
            break;
        }
    }

    // Enviar el comando de reinicio al puerto 0x64
    __asm__ volatile (
        "outb %0, %1"              // Enviar un comando al puerto
        :                          // No hay salida
        : "a"((unsigned char)0xFE), "Nd"(0x64)  // Valor inmediato en %al, puerto 0x64
    );

    // Si el reinicio falla, mantener un bucle infinito
    while (1);
}

// Prototipo de la función para apagar el sistema
void shutdown_system();

// Implementación de shutdown_system
void shutdown_system() {
    // Deshabilitar las interrupciones
    __asm__ volatile("cli");

    // Solicitar el apagado a través de la BIOS usando APM
    __asm__ volatile (
        "mov $0x5307, %ax\n"  // Función APM: APAGADO
        "mov $0x0001, %bx\n"  // Solicitud para apagar el sistema
        "mov $0x0003, %cx\n"  // Estado del dispositivo: Apagar
        "int $0x15\n"         // Llamada a la interrupción de APM
    );

    // Si el apagado falla, permanecer en un bucle infinito
    while (1);
}

// Ejemplo de uso dentro del kernel




// Prototipo de la función

// PANIC's.





// DRIVERS








// sound driver

#define SOUND_COMMAND_PORT 0x388  // Ejemplo de puerto base del hardware de sonido
#define SOUND_DATA_PORT 0x389    // Puerto para datos

// Función para escribir en un puerto (hardware directo)
static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Función para inicializar el hardware de sonido
void sound_init() {
    // Enviar un comando de inicialización al hardware
    outb(SOUND_COMMAND_PORT, 0x01); // Ejemplo de comando
    // Usando tu función para mensajes k_printf("Sonido inicializado.\n", 0, 0x0F); 
}

// Función para reproducir un tono
void play_tone(unsigned int frequency) {
   // Feedback al usuario del kernel  k_printf("Reproduciendo tono...\n", 1, 0x0F); 

    // Configurar la frecuencia del sonido
    outb(SOUND_DATA_PORT, (unsigned char)(frequency & 0xFF));       // Parte baja
    outb(SOUND_DATA_PORT + 1, (unsigned char)((frequency >> 8) & 0xFF)); // Parte alta
}

// Función para detener el sonido
void stop_tone() {
    // k_printf("Deteniendo tono...\n", 2, 0x0F); 
    outb(SOUND_COMMAND_PORT, 0x00); // Enviar comando de detener
}





// CPU




#define IDT_SIZE 256
#define KERNEL_CS 0x08 // Selector de segmento de código del kernel

// Estructura para una entrada en la IDT (Interrupt Descriptor Table)
struct idt_entry {
    unsigned short base_low;  // Bits bajos de la dirección del handler
    unsigned short sel;       // Segmento de código del handler
    unsigned char always0;    // Siempre 0
    unsigned char flags;      // Flags de tipo/privilegios
    unsigned short base_high; // Bits altos de la dirección del handler
} __attribute__((packed));    // Evitar padding

// Estructura para el registro de la IDT
struct idt_ptr {
    unsigned short limit;    // Tamaño de la IDT
    unsigned int base;       // Dirección base de la IDT
} __attribute__((packed));

struct idt_entry idt[IDT_SIZE];
struct idt_ptr idt_reg;

// Declaración de una función ASM para cargar la IDT
extern void load_idt(unsigned int);

// Función para configurar una entrada en la IDT
void set_idt_gate(int n, unsigned int handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].base_high = (handler >> 16) & 0xFFFF;
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; // Interrupción presente y privilegio del kernel
}

// Inicializar la IDT
void init_idt() {
    idt_reg.base = (unsigned int)&idt;
    idt_reg.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;

    // Configurar una interrupción para manejar excepciones
    set_idt_gate(0, (unsigned int)isr0_handler);

    // Cargar la IDT
    load_idt((unsigned int)&idt_reg);
    // k_printf("IDT inicializada.\n", 0, 0x0F);
}

// Ejemplo de manejador de interrupción
void isr0_handler() {
    // k_printf("Interrupción 0 recibida.\n", 1, 0x04);
    while (1); // Detiene la ejecución en caso de excepción crítica
}








// gpu







#define VIDEO_MEMORY 0xA0000 // Dirección base de memoria VGA
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

// Función para configurar el modo de video VGA (320x200x256 colores)
void set_video_mode() {
    // Usamos la interrupción del BIOS 0x10 para cambiar al modo 0x13
    __asm__ volatile (
        "mov $0x13, %ax\n"  // Establecer modo 0x13
        "int $0x10\n"       // Interrupción BIOS para video
    );
}

// Función para dibujar un píxel directamente en la memoria de video
void draw_pixel_gpu(int x, int y, unsigned char color) {
    char *video = (char *)VIDEO_MEMORY; // Puntero a memoria VGA
    video[(y * SCREEN_WIDTH) + x] = color; // Escribir en la posición adecuada
}

// Función para rellenar la pantalla con un color
void fill_screen(unsigned char color) {
    char *video = (char *)VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video[i] = color; // Llenar cada byte de memoria con el color dado
    }
}






// VIDEO






// Definimos nuestro propio tipo uint8_t como un entero sin signo de 8 bits
typedef unsigned char uint8_t;

// Definimos las dimensiones de la pantalla y la memoria de video
#define VIDEO_MEMORY 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

// Fuente predeterminada
uint8_t defaultFont[128][8] = {
    {0x00, 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x18, 0x00}, // Ejemplo de carácter "!"
    {0x00, 0x00, 0x7E, 0x81, 0x81, 0x81, 0x7E, 0x00}, // Ejemplo de carácter "O"
    // Otros caracteres aquí...
};

// Prototipos de funciones
void draw_pixel(int x, int y, uint8_t color);
void draw_char(int x, int y, char c, uint8_t color);
void draw_string(int x, int y, const char *str, uint8_t color);

// Implementación para dibujar un píxel en pantalla
void draw_pixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        char *video = (char *)VIDEO_MEMORY;
        video[(y * SCREEN_WIDTH) + x] = color;
    }
}

// Implementación para dibujar un carácter usando la fuente
void draw_char(int x, int y, char c, uint8_t color) {
    uint8_t *glyph = defaultFont[(int)c];
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (glyph[row] & (0x80 >> col)) {
                draw_pixel(x + col, y + row, color);
            }
        }
    }
}

// Implementación para dibujar una cadena de texto
void draw_string(int x, int y, const char *str, uint8_t color) {
    while (*str) {
        draw_char(x, y, *str, color);
        x += 8; // Avanza 8 píxeles por carácter
        str++;
    }
}

// Función principal del kernel
/*void kernel_main() {
    // Cambiamos al modo gráfico VGA (320x200)
    __asm__ volatile (
        "mov $0x13, %ax\n"  // Modo VGA 13h
        "int $0x10\n"       // Interrupción del BIOS
    );

    // Limpiamos la pantalla con un color de fondo
    char *video = (char *)VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video[i] = 0x01; // Azul oscuro
    }

    // Dibujamos texto en pantalla
    draw_string(10, 10, "Hello, BearOS!", 0x0F); // Blanco

    // Bucle infinito para mantener el sistema en ejecución
    while (1);
}*/









#include "include/colors.h"
#include "include/keyboard.h"
#include "include/disk.h"
#include "include/INFO.h"








void W_MSG() {
    k_clear_screen();
    k_printf_center("+--------------------------------------------------+", 0, WHITE_TXT); 
    k_printf_center("|                                                  |", 1, WHITE_TXT); 
    k_printf_center("|                                                  |", 2, WHITE_TXT); 
    k_printf_center("|        1000001    00000   1000    10000          |", 3, WHITE_TXT); 
    k_printf_center("|       10    00   00      10  00  10   00         |", 4, WHITE_TXT); 
    k_printf_center("|       0000010    000000  00  00  00   0          |", 5, WHITE_TXT); 
    k_printf_center("|       00     0   00      000000  00001           |", 6, WHITE_TXT); 
    k_printf_center("|       00   01    10   00 00  00  00 00           |", 7, WHITE_TXT); 
    k_printf_center("|       10000       0000   10  01  01  10          |", 8, WHITE_TXT); 
    k_printf_center("|                                                  |", 9, WHITE_TXT); 
    k_printf_center("|                                                  |", 10, WHITE_TXT); 
    k_printf_center("|                                                  |", 11, WHITE_TXT); 
    k_printf_center("|                                                  |", 12, WHITE_TXT); 
    k_printf_center("|            BEAR: OS kernel (v0.11.0)             |", 13, WHITE_TXT); 
    k_printf_center("|                                                  |", 14, WHITE_TXT); 
    k_printf_center("|                                                  |", 15, WHITE_TXT); 
    k_printf_center("+--------------------------------------------------+", 16, WHITE_TXT); 
    k_printf_center("AUTHOR: NopAngel", 17, ORANGE_TXT); 


}



volatile unsigned char current_bg_color = BLACK_BG; // Color de fondo por defecto



int strlen(const char *str) {
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}


int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


int strncmp(const char *str1, const char *str2, unsigned int n) {
    while (n && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
        n--;
    }
    if (n == 0) {
        return 0; // Son iguales hasta los primeros n caracteres
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


char *custom_strcpy(char *dest, const char *src) {
    char *dest_start = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Termina la cadena con un carácter nulo
    return dest_start;
}
char *strcpy(char *dest, const char *src) {
    char *dest_start = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; // Termina la cadena con un carácter nulo
    return dest_start;
}



typedef struct {
    char name[MAX_FILENAME_LENGTH]; // Nombre del archivo
    unsigned int size;              // Tamaño del archivo (en bytes)
    unsigned int start_block;       // Bloque inicial en el disco virtual
} FileEntry;

#define TRUE 1
#define FALSE 0
typedef int bool;

unsigned int custom_strlen(const char *str) {
    unsigned int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}



// Tabla de archivos en memoria
FileEntry file_table[MAX_FILES];
unsigned int file_count = 0; // Número de archivos creados


// Simulación del disco virtual
char virtual_disk[DISK_SIZE];

// Estructura para una entrada de directorio
typedef struct {
    char name[MAX_NAME_LENGTH]; // Nombre del directorio
    unsigned int start_block;   // Bloque inicial en el disco
    unsigned int size;          // Tamaño del directorio (en bloques)
} DirectoryEntry;

// Tabla de directorios en memoria
DirectoryEntry directory_table[MAX_DIRECTORIES];
unsigned int directory_count = 0; // Número de directorios creados


void create_new_file(const char *filename) {
    int cursor_y = 0;
    custom_strcpy(file_table[file_count].name, filename);
    file_table[file_count].size = 0;
    file_table[file_count].start_block = directory_count * 16 + file_count;
    file_count++;

    k_printf("Archivo creado: ", cursor_y++, GREEN_TXT);
    k_printf_no_newline(filename, cursor_y++, WHITE_TXT);
}

int touch(const char *filename) {
    create_new_file(filename);
    return 0;
}







void set_background_color(const char *color_name) {
    // Determinar el color según el nombre
    if (strcmp(color_name, "white") == 0) {
        current_bg_color = WHITE_BG;
    } else if (strcmp(color_name, "gray") == 0) {
        current_bg_color = GRAY_BG;
    } else if (strcmp(color_name, "aqua") == 0) {
        current_bg_color = AQUA_BG;
    } else if (strcmp(color_name, "red") == 0) {
        current_bg_color = RED_BG;
    } else if (strcmp(color_name, "blue") == 0) {
        current_bg_color = BLUE_BG;
    } else if (strcmp(color_name, "purple") == 0) {
        current_bg_color = PURPLE_BG;
    } else if (strcmp(color_name, "orange") == 0) {
        current_bg_color = ORANGE_BG;
    } else if (strcmp(color_name, "black") == 0) {
        current_bg_color = BLACK_BG;
    } else if (strcmp(color_name, "pink") == 0) {
        current_bg_color = PINK_BG;
    } else if (strcmp(color_name, "green") == 0) {
        current_bg_color = GREEN_BG;
    } else if (strcmp(color_name, "darkblue") == 0) {
        current_bg_color = DARKBLUE_BG;
    } else {
        k_printf("Error: Color no reconocido.\n", 0, RED_TXT);
        return;
    }

    // Cambiar el color de fondo en toda la pantalla
    char *vidmem = (char *)0xb8000;
    for (int i = 0; i < SCREEN_ROWS * SCREEN_COLUMNS; i++) {
        vidmem[i * 2 + 1] = current_bg_color; // Cambia el atributo de color
    }
}


void list_items() {
    int cursor_y = 0;

    // Listar directorios
    if (directory_count > 0) {
        k_printf("Directorios:\n", cursor_y++, BLUE_TXT);
        for (unsigned int i = 0; i < directory_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            k_printf_no_newline(directory_table[i].name, cursor_y++, WHITE_TXT);
            k_printf_no_newline("- apm", cursor_y++, BLUE_TXT);
            k_printf_no_newline("\n", cursor_y++, WHITE_TXT);
        }
    }
    cursor_y = cursor_y + 7;

    // Listar archivos
    if (file_count > 0) {
        k_printf("Archivos:\n", cursor_y++, GREEN_TXT);
        for (unsigned int i = 0; i < file_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            k_printf_no_newline(file_table[i].name, cursor_y++, WHITE_TXT);
            k_printf_no_newline("- apm (archivo del sistema)", cursor_y++, BLUE_TXT);

        }
    }

    // Si no hay contenido
    if (directory_count == 0 && file_count == 0) {
        k_printf("No hay contenido.\n", 1, WHITE_TXT);
        k_printf_no_newline("- apm (archivo del sistema)", cursor_y++, BLUE_TXT);

    }
}



void W_MSG();






int mkdir(const char *dirname) {
    // Verificar si se alcanzó el máximo de directorios
    if (directory_count >= MAX_DIRECTORIES) {
        k_printf("Error: No se pueden crear más directorios.\n", 0, RED_TXT);
        return -1;
    }

    // Verificar si el nombre del directorio es demasiado largo
    if (strlen(dirname) >= MAX_NAME_LENGTH) {
        k_printf("Error: El nombre del directorio es demasiado largo.\n", 0, RED_TXT);
        return -1;
    }

    // Verificar si el directorio ya existe
    for (unsigned int i = 0; i < directory_count; i++) {
        if (strcmp(directory_table[i].name, dirname) == 0) {
            k_printf("Error: El directorio ya existe.\n", 0, RED_TXT);
            return -1;
        }
    }

    // Crear el nuevo directorio
    strcpy(directory_table[directory_count].name, dirname); // Usar directory_count como índice
    directory_table[directory_count].start_block = directory_count * 16; // Bloques consecutivos
    directory_table[directory_count].size = 16; // Tamaño asignado
    directory_count++; // Incrementar el contador

    k_printf("Directorio creado: ", 0, GREEN_TXT);
    k_printf_no_newline(dirname, 0, WHITE_TXT);
    k_printf_no_newline("\n", 0, WHITE_TXT);

    return 0;
}




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

// Tabla simplificada de scancodes a ASCII
const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0F
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '´', '+', '\n', 0, // 0x10 - 0x1F
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',      // 0x20 - 0x2D
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,   // 0x2E - 0x3F
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,            // 0x40 - 0x4F
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0             // 0x50 - 0x5F
};



void scroll_screen() {
    // Desplazar todas las líneas hacia arriba
    for (int i = 1; i < SCREEN_ROWS; i++) {
        for (int j = 0; j < SCREEN_COLUMNS * 2; j++) {
            SCREEN_BUFFER[(i - 1) * SCREEN_COLUMNS * 2 + j] =
                SCREEN_BUFFER[i * SCREEN_COLUMNS * 2 + j];
        }
    }

    // Limpiar la última línea
    for (int j = 0; j < SCREEN_COLUMNS * 2; j++) {
        SCREEN_BUFFER[(SCREEN_ROWS - 1) * SCREEN_COLUMNS * 2 + j] = 0;
    }

    cursor_y = SCREEN_ROWS - 1; // Ajustar el cursor a la última fila
    cursor_x = 0;               // Reiniciar el cursor al inicio de la línea
}


// Escribe un carácter en la pantalla
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






































// Procesar el contenido del buffer de entrada cuando se presiona Enter
void process_input() {
    input_buffer[input_index] = '\0'; // Termina la cadena con un carácter nulo

    // Verificar si el usuario ingresó "test"
    if (strcmp(input_buffer, "test") == 0) {
        k_printf("Hello, World!", cursor_y, GREEN_TXT); // Respuesta
        cursor_y++;
    } else if (strcmp(input_buffer, "bearfetch") == 0) {
        k_clear_screen();
        cursor_y = 0;
        k_printf(" BEAR OS ", cursor_y++, ORANGE_TXT);
        k_printf("AUTHOR: NopAngel", cursor_y++, GRAY_TXT);
        k_printf("Repository: github.com/NopAngel/bear", cursor_y++, RED_TXT);
    } else if (strcmp(input_buffer, "reboot") == 0) {

        __asm__ volatile (
        "mov $0x13, %ax\n"  // Modo VGA 13h
        "int $0x10\n"       // Interrupción del BIOS
    );

    // Simular algún escenario crítico y luego reiniciar
    k_printf("Reiniciando el sistema en 5 segundos...", 1, RED_TXT);

    // Esperar (simulada, por simplicidad)
    for (volatile int i = 0; i < 50000000; i++) { }

    reboot_system();    
    } else if (strcmp(input_buffer, "shutdown") == 0) {
        __asm__ volatile (
        "mov $0x13, %ax\n"  // Modo VGA 13h
        "int $0x10\n"       // Interrupción del BIOS
    );

    // Simular un mensaje antes del apagado
    k_printf("Apagando el sistema en 5 segundos...", 0, RED_TXT);

    // Esperar un tiempo antes de apagar (simulada con un bucle)
    for (volatile int i = 0; i < 50000000; i++) { }

    // Llamar a la función de apagado
    shutdown_system();
    }



     else if (strcmp(input_buffer, "inf") == 0) {
        k_clear_screen();
        cursor_y = 10;
        k_printf("ANGEL - BEAR OS", cursor_y++, WHITE_TXT);
        k_printf("B E A R OS [2024-2025]", cursor_y++, WHITE_TXT);
        k_printf("EP. 1: HISTORY AND CONTEXT.", cursor_y++, WHITE_TXT);
        k_printf(" - CONTEXT:", cursor_y++, WHITE_TXT);
        k_printf("  What is BearOS? BearOS is an operating system (kernel) designed for programmers \n (both new and advanced). It's inspired by Linux, but with \n easier-to-understand commands and more. The creator \n (NopAngel, also known as Angel Nieto) was inspired by Linux when creating this OS (kernel). \n He spent almost 2 years developing it. \n Even though he doesn't have much experience creating an OS, \n he tried. Just take inspiration from this. If he could create an OS (kernel) without much experience in C and programming, you can too :) Happy day/afternoon/evening, coder!", cursor_y++, WHITE_TXT);

    
    }else if (strcmp(input_buffer, "about") == 0) {
        k_clear_screen();
        cursor_y = 0;
        k_printf_center("about", cursor_y++, WHITE_TXT);
        k_printf_center("bear OS", cursor_y++, WHITE_TXT);
        k_printf_center("The Bear operating system.", cursor_y++, WHITE_TXT);
        k_printf_center("v0.1", cursor_y++, WHITE_TXT);
        k_printf_center("Copyright @ 2024-2025", cursor_y++, WHITE_TXT);
        k_printf_center("NopAngel & contributors.", cursor_y++, GRAY_TXT);
    
    }


    else if (strncmp(input_buffer, "print ", 6) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 6;
        k_printf(value, cursor_y++, WHITE_TXT);
    }else if (strncmp(input_buffer, "print-red ", 10) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 10;
        k_printf(value, cursor_y++, RED_TXT);
    }else if (strncmp(input_buffer, "print-green ", 13) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 13;
        k_printf(value, cursor_y++, GREEN_TXT);
    }else if (strncmp(input_buffer, "print-blue ", 11) == 0) {
        cursor_y = cursor_y + 11;
        const char *value = input_buffer + 6;
        k_printf(value, cursor_y++, BLUE_TXT);
    }



    else if (strcmp(input_buffer, "help") == 0) {
        k_clear_screen();
        cursor_y = 10;
        k_printf("HELP COMMANDS", cursor_y++, ORANGE_TXT);
        k_printf("cd: Te translada a diferente carpeta (parametros: nombre de carpeta)", cursor_y++, WHITE_TXT); 
        k_printf("mkdir: Crea una carpeta (parametros: nombre de carpeta)", cursor_y++, WHITE_TXT); 
        k_printf("rmd: Elimina una carpeta (parametros: nombre de carpeta)", cursor_y++, WHITE_TXT); 
        k_printf("rm: Elimina un archivo (parametros: nombre de archivo)", cursor_y++, WHITE_TXT); 
        k_printf("bearfetch: Muestra la informacion de tu PC (parametros: ninguno)", cursor_y++, WHITE_TXT); 
        k_printf("test: Muestra un mensaje de 'Hello, world!' (parametros: ninguno)", cursor_y++, WHITE_TXT); 
        k_printf("help: Muestra este mensaje de ayuda (parametros: ninguno)", cursor_y++, WHITE_TXT); 
        k_printf("sh: Muestra la version de la terminal de este kernel (parametros: ninguno)", cursor_y++, WHITE_TXT); 
        k_printf("man: Muestra la informacion detallada de archivo (parametros: nombre del archivo)", cursor_y++, WHITE_TXT); 
        k_printf("touch: Crea un archivo (parametros: nombre del archivo, con su respectiva extension)", cursor_y++, WHITE_TXT); 
    } else if (strncmp(input_buffer, "setbg/", 6U) == 0) {
    const char *color_name = input_buffer + 6; // Extraer el nombre del color
    set_background_color(color_name);         // Cambiar el color de fondo
}
else if (strcmp(input_buffer, "repo") == 0) {
        k_printf("Repositorio: github.com/NopAngel/bear", cursor_y++, GRAY_TXT);
    }else if (strncmp(input_buffer, "mkdir ", 6) == 0) {
        const char *dirname = input_buffer + 6;
        cursor_y = 20;

        mkdir(dirname);
    }
    // Comando touch
    else if (strncmp(input_buffer, "touch ", 6) == 0) {
        const char *filename = input_buffer + 6;
        cursor_y = 20;

        touch(filename);
    }else if (strncmp(input_buffer, "pwd", 6) == 0) {
        k_printf("Home>", cursor_y++, GREEN_TXT);
    }
    // Comando ls
    else if (strcmp(input_buffer, "ls") == 0) {
        k_clear_screen();
        cursor_y = 20;
        list_items();
    }

    else if (strcmp(input_buffer, "bear") == 0) {
        k_printf("KERNEL PANIC: OH NO!!! Los BEARS han tomado el control (FATAL ERROR)", cursor_y++, RED_TXT);
    }
     else if (strcmp(input_buffer, "clear") == 0) {
        k_clear_screen();
        cursor_y = 0; // Resetear debajo del mensaje de bienvenida
    }
else if (strcmp(input_buffer, "sh") == 0) {
        k_printf("BearSH v1.3", cursor_y++, GREEN_TXT);
        }
     else {
        k_printf("Comando no reconocido.", cursor_y++, RED_TXT); // Mensaje por defecto
    }

    // Después de cada línea, verificamos si el cursor ha llegado al límite
    if (cursor_y >= SCREEN_ROWS) {
        scroll_screen(); // Llama a la función de scroll
    }

    // Reiniciar el buffer de entrada
    input_index = 0;
    cursor_x = 0;
}


// Controlador de teclado con soporte para backspace, espacio y enter
/*
void keyboard_handler() {
    unsigned char scancode = read_scancode();

    if (scancode == last_scancode) {
        return;
    }

    last_scancode = scancode;

    if (scancode < sizeof(scancode_to_ascii)) {
        char ascii = scancode_to_ascii[scancode];

        // Manejar teclas especiales
        if (ascii == '\b') { // Backspace
            if (input_index > 0) {
                input_index--; // Retroceder en el buffer
                if (cursor_x > 0) {
                    cursor_x--;
                } else if (cursor_y > 0) {
                    cursor_y--;
                    cursor_x = SCREEN_COLUMNS - 1;
                }

                int pos = (cursor_y * SCREEN_COLUMNS + cursor_x) * 2;
                SCREEN_BUFFER[pos] = ' ';
                SCREEN_BUFFER[pos + 1] = 0x07;
            }
        } else if (ascii == '\n') { // Enter
            process_input(); // Procesar el comando ingresado
        } else if (ascii) { // Otros caracteres
            if (input_index < INPUT_BUFFER_SIZE - 1) { // Evitar desbordamiento
                input_buffer[input_index++] = ascii;
                put_char(ascii);
            }
        }
    }
}


*/







// Variables globales para manejar el estado de las teclas modificadoras
int caps_lock = 0;         // Estado de Caps Lock
int shift_pressed = 0;     // Estado de Shift (izquierdo o derecho)

void keyboard_handler() {
    unsigned char scancode = read_scancode();

    // Evitar procesar el mismo scancode repetidamente
    if (scancode == last_scancode) {
        return;
    }

    last_scancode = scancode;

    // Comprobar si es un scancode de liberación (release)
    if (scancode & 0x80) {
        // Convertir el scancode a pulsación (key press)
        scancode &= 0x7F;

        // Detectar si se liberó Shift
        if (scancode == 0x2A || scancode == 0x36) { // Shift izquierdo o derecho
            shift_pressed = 0;
        }

        return;
    } else {
        // Detectar teclas modificadoras (Shift y Caps Lock)
        if (scancode == 0x2A || scancode == 0x36) { // Shift izquierdo o derecho
            shift_pressed = 1;
            return;
        } else if (scancode == 0x3A) { // Caps Lock
            caps_lock = !caps_lock; // Alternar estado de Caps Lock
            return;
        }
    }

    // Si el scancode corresponde a un carácter imprimible
    if (scancode < sizeof(scancode_to_ascii)) {
        char ascii = scancode_to_ascii[scancode];

        // Convertir a mayúsculas si Caps Lock o Shift están activos
        if ((caps_lock || shift_pressed) && ascii >= 'a' && ascii <= 'z') {
            ascii -= 32; // Convertir minúscula a mayúscula
        } else if (shift_pressed && ascii >= '1' && ascii <= '9') {
            // Manejar símbolos asociados a los números con Shift
            switch (ascii) {
                case '1': ascii = '!'; break;
                case '2': ascii = '@'; break;
                case '3': ascii = '#'; break;
                case '4': ascii = '$'; break;
                case '5': ascii = '%'; break;
                case '6': ascii = '^'; break;
                case '7': ascii = '&'; break;
                case '8': ascii = '*'; break;
                case '9': ascii = '('; break;
                case '0': ascii = ')'; break;
            }
        }

        // Manejar teclas especiales
        if (ascii == '\b') { // Backspace
            if (input_index > 0) {
                input_index--; // Retroceder en el buffer
                if (cursor_x > 0) {
                    cursor_x--;
                } else if (cursor_y > 0) {
                    cursor_y--;
                    cursor_x = SCREEN_COLUMNS - 1;
                }

                int pos = (cursor_y * SCREEN_COLUMNS + cursor_x) * 2;
                SCREEN_BUFFER[pos] = ' ';
                SCREEN_BUFFER[pos + 1] = 0x07;
            }
        } else if (ascii == '\n') { // Enter
            process_input(); // Procesar el comando ingresado
        } else if (ascii) { // Otros caracteres
            if (input_index < INPUT_BUFFER_SIZE - 1) { // Evitar desbordamiento
                input_buffer[input_index++] = ascii;
                put_char(ascii); // Escribir carácter en pantalla
            }
        }
    }
}





void k_main() 
{
    k_clear_screen();
    W_MSG();
    
    // Ajustar el cursor para empezar a escribir debajo del mensaje de bienvenida
    cursor_x = 0;
    cursor_y = 19; // Empieza en la fila 8 (debajo del mensaje de bienvenida)


    
    init_idt(); 
    sound_init();




    init_shared_memory();

    // Proceso 1: Reservar un bloque de memoria compartida
    void *block1 = allocate_shared_memory(512);

    // Proceso 2: Reservar otro bloque
    void *block2 = allocate_shared_memory(512);

    // Proceso 1: Liberar el bloque
    free_shared_memory(block1);


    // Reasignación




    /*__asm__ volatile (
        "mov $0x13, %ax\n"
        "int $0x10\n"
    );

    // Rellenar pantalla con un color
    char *video = (char *)VIDEO_MEMORY;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video[i] = 0x01; // Azul oscuro
    }

    // Dibujar texto
    draw_string(10, 10, "Hello, BearOS!", 0x0F); // Blanco
    */

    while (1) {
        keyboard_handler();
    }
};

void k_clear_screen()
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
};

unsigned int k_printf_no_newline(const char *message, unsigned int line, unsigned int color) {
    char *vidmem = (char *) 0xb8000;
    unsigned int i = (line * 80 * 2);

    while (*message != 0) {
        vidmem[i] = *message;      // Escribe el carácter en memoria de video
        message++;
        i++;
        vidmem[i] = color;         // Escribe el color
        i++;
    }

    return 1; // Indica éxito
}




unsigned int k_printf(char *message, unsigned int line, unsigned int color)
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;

	i=(line*80*2);

	while(*message!=0)
	{
		if(*message=='\n') // chec1k for a new line (upgrated)
		{
			line++;
			i=(line*80*2);
			*message++;
		} else {
			vidmem[i]=*message;
			*message++;
			i++;
			vidmem[i]=color;
			i++;
		};
	};

	return(1);
}

unsigned int k_printf_center(char *message, unsigned int line, unsigned int color) {
    char *vidmem = (char *) 0xb8000;
    unsigned int i = 0;
    unsigned int length = 0;

    // Calcular la longitud del mensaje
    char *ptr = message;
    while (*ptr != 0) {
        length++;
        ptr++;
    }

    // Calcular el número de espacios en blanco necesarios para centrar
    unsigned int padding = (80 - length) / 2;

    // Calcular la posición inicial en memoria de video
    i = (line * 80 * 2) + (padding * 2);

    // Escribir el mensaje en la memoria de video
    while (*message != 0) {
        if (*message == '\n') { // Manejo de nueva línea
            line++;
            padding = (80 - length) / 2;
            i = (line * 80 * 2) + (padding * 2);
            message++;
        } else {
            vidmem[i] = *message;
            message++;
            i++;
            vidmem[i] = color;
            i++;
        }
    }

    return 1;
}


/*

void W_MSG(){
    set_background_color("orange");         

   k_printf("                                                    ", 0, WHITE_BG_BLACK);
   k_printf("                                                    ", 1, WHITE_BG_BLACK);

   k_printf("                       bearOS                       ", 2, WHITE_BG_BLACK);
   k_printf("                                   ", 3, WHITE_BG_BLACK);
   k_printf("                       LOADING                      ", 3, WHITE_BG_BLACK);
   k_printf("                                                    ", 4, WHITE_BG_BLACK);

   k_printf("                                                    ", 5, WHITE_BG_BLACK);


}*/



