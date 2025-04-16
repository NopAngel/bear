
/*
				B - E - A - R      OS

						LICENSE: APACHE 2.0
						Author: NopAngel
						Repository: NopAngel

           - What you're seeing is the (main) code that makes the kernel work.
                (Libraries and similar things are also imported from the project.)

             This project is for funny purposes only and has its own commercial license.
                        Thanks for watching! :)


     @Copyright 2024-2025 - BearOS - PAGE: https://bearos.vercel.com/ 
*/



// Context: I've just finished creating the "final" version for v2.0 (FULL), and yes... The code is very disorganized, 
// but this is because there is no such thing as "perfect code." Obviously, 
//this OS can be improved 1,000%, but I don't really care that much. The code is going to stay like this for a while, 
// because it does its job, it'll be fast, it'll work well, and nothing else. I just wanted to put this out there.


#define MAX_NAME_LENGTH 256
#define MAX_CONTENT_LENGTH 1024
int cursor_x = 0;   
int cursor_y = 0; 
int input_index = 0;    


volatile unsigned char last_scancode = 0;

int LOGIN = 1;
void k_clear_screen();
#include "fs/k_printf.h"
#include "reboot.h"
#include "include/multiboot.h"
#include "shutdown.h"
#include "panic/panic.h"

void set_background_color(const char *color_name);
unsigned int k_printf(char *message, unsigned int line, unsigned int color);
unsigned int k_printf_no_newline(const char *message, unsigned int line, unsigned int color);
unsigned int k_printf_center(char *message, unsigned int line, unsigned int color);
typedef unsigned char uint8_t;  
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;  
typedef unsigned long long uint64_t; 

#define KERNEL_M_ALPHA_NAME "BearX"
#define AUTHOR_X_KERNEL "NopAngel (Angel Nieto)"
#define LICENSE_X_KERNEL "Apache 2.0"
#define M_N_KERNEL "BearOS (x86)"

/*
*   Explanation: These "#define's" act as a kind of credit, which is what it is used for to note.
*
*   - M = Max
*   - X = 10
*   - N = Name
*/ 



// K_PRINTF WITH FONT!?!??!?!?!? LOLLLLLLLLLLL - YEAH, I was doing it, but i was too lazy lol.

/*
*
*
*
*
*
*
*
*
*
*
*
*   The website has just been created, I left this comment just in case 
*you see/read this, go to the website, there is the documentation, and more information 
*about BearOS, take a look and see :)
*
*  https://bearos.vercel.com/ - Yes, it is hosted by VERCEL, they don't ask for much HEHE
*
*
*
*

*

*
*
*
*
*
*/







void free_shared_memory(void *address);
void init_shared_memory();
void kernel_panic(const char *message);


// SHARED MEMORY'S




void *allocate_shared_memory(unsigned int size);
void free_shared_memory(void *address);
void init_shared_memory();


#define SHARED_MEMORY_SIZE 4096
#define MAX_SHARED_BLOCKS 8     

typedef struct {
    int is_used;             
    void *start_address;      
    unsigned int size;  
} shared_block_t;

shared_block_t shared_blocks[MAX_SHARED_BLOCKS];
void *shared_memory_base = (void *)0x100000;


void init_shared_memory() {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        shared_blocks[i].is_used = 0;
        shared_blocks[i].start_address = shared_memory_base + (i * (SHARED_MEMORY_SIZE / MAX_SHARED_BLOCKS));
        shared_blocks[i].size = SHARED_MEMORY_SIZE / MAX_SHARED_BLOCKS;
    }
}


void *allocate_shared_memory(unsigned int size) {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        if (!shared_blocks[i].is_used && shared_blocks[i].size >= size) {
            shared_blocks[i].is_used = 1; 
            return shared_blocks[i].start_address;
        }
    }
    return 0; 
}

void free_shared_memory(void *address) {
    for (int i = 0; i < MAX_SHARED_BLOCKS; i++) {
        if (shared_blocks[i].start_address == address) {
            shared_blocks[i].is_used = 0;
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









// DRIVERS








// sound driver

#define SOUND_COMMAND_PORT 0x388 
#define SOUND_DATA_PORT 0x389    


static inline void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void sound_init() {
    outb(SOUND_COMMAND_PORT, 0x01); 
}

void play_tone(unsigned int frequency) {



    outb(SOUND_DATA_PORT, (unsigned char)(frequency & 0xFF)); 
    outb(SOUND_DATA_PORT + 1, (unsigned char)((frequency >> 8) & 0xFF)); 
}


void stop_tone() {

    outb(SOUND_COMMAND_PORT, 0x00);
}




















#include "include/colors.h"
#include "include/keyboard.h"
#include "include/disk.h"
#include "include/INFO.h"
void W_MSG_NOT() {
    k_printf("hi user! :)", 0, WHITE_TXT);
    k_printf("please logged", 1, WHITE_TXT);
}

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
    k_printf_center("|        00000      0000   10  01  01  10          |", 8, WHITE_TXT); 
    k_printf_center("|                                                  |", 9, WHITE_TXT); 
    k_printf_center("|                                                  |", 10, WHITE_TXT); 
    k_printf_center("|                                                  |", 11, WHITE_TXT); 
    k_printf_center("|                                                  |", 12, WHITE_TXT); 
    k_printf_center("|            BEAR: OS kernel (2.0)                 |", 13, WHITE_TXT); 
    k_printf_center("|                                                  |", 14, WHITE_TXT); 
    k_printf_center("|                                                  |", 15, WHITE_TXT); 
    k_printf_center("+--------------------------------------------------+", 16, WHITE_TXT); 
    k_printf_center("AUTHOR: NopAngel", 17, ORANGE_TXT); 


}



volatile unsigned char current_bg_color = BLACK_BG;



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
        return 0; 
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int custom_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
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
    *dest = '\0'; 
    return dest_start;
}
char *strcpy(char *dest, const char *src) {
    char *dest_start = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; 
    return dest_start;
}



typedef struct {
    char name[MAX_NAME_LENGTH];    
    unsigned int start_block;     
    unsigned int size;             
    char content[MAX_CONTENT_LENGTH];
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



FileEntry file_table[MAX_FILES];

#define MAX_CONTENT_LENGTH 1024

unsigned int file_count = 0; 


char content[MAX_CONTENT_LENGTH];

char virtual_disk[DISK_SIZE];





typedef struct {
    char name[MAX_NAME_LENGTH];  
    unsigned int start_block;  
    unsigned int size;           
} DirectoryEntry;
#define MAX_LINES 10000

DirectoryEntry directory_table[MAX_DIRECTORIES];
unsigned int directory_count = 0;
void create_new_file(const char *filename, const char *content) {
    custom_strcpy(file_table[file_count].name, filename);   
    custom_strcpy(file_table[file_count].content, content); 
    file_table[file_count].size = custom_strlen(content);   
    file_table[file_count].start_block = directory_count * 16 + file_count;
    file_count++;
}


int touch(const char *filename, const char *content) {
    create_new_file(filename, content);
    return 0;
}



void update_file_content(const char *filename, const char *new_content) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) { 
            custom_strcpy(file_table[i].content, new_content);  
            file_table[i].size = custom_strlen(new_content);    
            return; 
        }
    }

    
}



void show_file_content(const char *filename) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) { 
            k_printf_no_newline(filename, 0, WHITE_TXT); 
            k_printf_no_newline(file_table[i].content, 0, WHITE_TXT); 
            return; 
        }
    }
   
    k_printf("Archivo no encontrado", 0, RED_TXT);
}




#define KEYBOARD_PORT 0x60     
#define STATUS_REGISTER 0x64  
#define OUTPUT_BUFFER_FULL 0x01
char input_buffer[INPUT_BUFFER_SIZE]; 









void set_background_color(const char *color_name) {
 
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


    char *vidmem = (char *)0xb8000;
    for (int i = 0; i < SCREEN_ROWS * SCREEN_COLUMNS; i++) {
        vidmem[i * 2 + 1] = current_bg_color; 
    }
}


void list_items() {
    int cursor_y = 0;


    if (directory_count > 0) {
        k_printf("Directorios:\n", cursor_y++, BLUE_TXT);
        for (unsigned int i = 0; i < directory_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            k_printf_no_newline(directory_table[i].name, cursor_y++, WHITE_TXT);
        }
    }
    cursor_y = cursor_y + 2;


    if (file_count > 0) {
        k_printf("Archivos:\n", cursor_y++, GREEN_TXT);
        for (unsigned int i = 0; i < file_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            k_printf_no_newline(file_table[i].name, cursor_y++, WHITE_TXT);

        }
    }


    if (directory_count == 0 && file_count == 0) {
        k_printf("No hay contenido.\n", 1, WHITE_TXT);

    }
}





void W_MSG();






int mkdir(const char *dirname) {

    if (directory_count >= MAX_DIRECTORIES) {
        k_printf("Error: No se pueden crear más directorios.\n", 0, RED_TXT);
        return -1;
    }


    if (strlen(dirname) >= MAX_NAME_LENGTH) {
        k_printf("Error: El nombre del directorio es demasiado largo.\n", 0, RED_TXT);
        return -1;
    }

    for (unsigned int i = 0; i < directory_count; i++) {
        if (strcmp(directory_table[i].name, dirname) == 0) {
            k_printf("Error: El directorio ya existe.\n", 0, RED_TXT);
            return -1;
        }
    }

 
    strcpy(directory_table[directory_count].name, dirname); 
    directory_table[directory_count].start_block = directory_count * 16; 
    directory_table[directory_count].size = 1; 
    directory_count++; 

    k_printf("Directorio creado: ", 0, GREEN_TXT);
    k_printf_no_newline(dirname, 0, WHITE_TXT);
    k_printf_no_newline("\n", 0, WHITE_TXT);

    return 0;
}







unsigned char read_scancode() {
    unsigned char scancode;
    asm volatile ("inb %1, %0" : "=a"(scancode) : "Nd"(KEYBOARD_PORT));
    return scancode;
}


const char scancode_to_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', // 0x00 - 0x0F
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '´', '+', '\n', 0, // 0x10 - 0x1F
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',      // 0x20 - 0x2D
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,   // 0x2E - 0x3F
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,            // 0x40 - 0x4F
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0             // 0x50 - 0x5F
};



void scroll_screen() {
 
    for (int i = 1; i < SCREEN_ROWS; i++) {
        for (int j = 0; j < SCREEN_COLUMNS * 2; j++) {
            SCREEN_BUFFER[(i - 1) * SCREEN_COLUMNS * 2 + j] =
                SCREEN_BUFFER[i * SCREEN_COLUMNS * 2 + j];
        }
    }

    for (int j = 0; j < SCREEN_COLUMNS * 2; j++) {
        SCREEN_BUFFER[(SCREEN_ROWS - 1) * SCREEN_COLUMNS * 2 + j] = 0;
    }

    cursor_y = SCREEN_ROWS - 1; 
    cursor_x = 0;             
}


void put_char(char c) {
    int pos = (cursor_y * SCREEN_COLUMNS + cursor_x) * 2;

    SCREEN_BUFFER[pos] = c;          
    SCREEN_BUFFER[pos + 1] = 0x07;  


    cursor_x++;
    if (cursor_x >= SCREEN_COLUMNS) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= SCREEN_ROWS) {
        scroll_screen(); 
    }
}























/*



void process_input_logged() {
    input_buffer[input_index] = '\0'; 


    if (strcmp(input_buffer, "test") == 0) {
        k_printf("Hello, World!", cursor_y, GREEN_TXT); 
        cursor_y++;
    } else if (strcmp(input_buffer, "bearfetch") == 0) {
        k_clear_screen();
        cursor_y = 0;
        k_printf(" BEAR OS ", cursor_y++, ORANGE_TXT);
        k_printf("AUTHOR: NopAngel", cursor_y++, GRAY_TXT);
        k_printf("Repository: github.com/NopAngel/bear", cursor_y++, RED_TXT);
    } else if(strcmp(input_buffer, "bear") == 0) {
        k_printf("logged! welcome user bear!!!", 6, WHITE_TXT);
        LOGIN = 1;
        k_clear_screen();
        W_MSG();
    }
     else {
        k_printf("Comando no reconocido.", cursor_y++, RED_TXT); 
    }


    if (cursor_y >= SCREEN_ROWS) {
        scroll_screen();
    }

  
    input_index = 0;
    cursor_x = 0;
}*/



















void process_input() {
    input_buffer[input_index] = '\0'; 


    if (strcmp(input_buffer, "test") == 0) {
        k_printf("Hello, World!", cursor_y, GREEN_TXT); 
        cursor_y++;
    }

    
else if (strcmp(input_buffer, "reboot") == 0) {

    


    k_clear_screen();
    k_printf("Resetting the system in 5 seconds...", 1, RED_TXT);


    for (volatile int i = 0; i < 50000000; i++) {      }

    reboot_system();    
    } else if (strcmp(input_buffer, "shutdown") == 0) {
        __asm__ volatile (
        "mov $0x13, %ax\n" 
        "int $0x10\n"       
    );

   
    k_printf("Shutting the system in 5 seconds...", 0, RED_TXT);

    for (volatile int i = 0; i < 50000000; i++) { }

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

    
    }
  
    
    else if (strcmp(input_buffer, "about") == 0) {
        k_clear_screen();
        cursor_y = 0;
        k_printf_center("about", cursor_y++, WHITE_TXT);
        k_printf_center("bear OS", cursor_y++, WHITE_TXT);
        k_printf_center("The Bear operating system.", cursor_y++, WHITE_TXT);
        k_printf_center("v2", cursor_y++, WHITE_TXT);
        k_printf_center("Copyright @ 2024-2025", cursor_y++, WHITE_TXT);
        k_printf_center("NopAngel & contributors.", cursor_y++, GRAY_TXT);
    
    }

    else if (strncmp(input_buffer, "print ", 6) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 6;
        k_printf(value, cursor_y++, WHITE_TXT);
    }


    else if (strncmp(input_buffer, "print ", 6) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 6;
        k_printf(value, cursor_y++, WHITE_TXT);
    }   
    else if (strncmp(input_buffer, "print-red ", 10) == 0) {
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
    const char *color_name = input_buffer + 6; 
    set_background_color(color_name);         
}
else if (strcmp(input_buffer, "repo") == 0) {
        k_printf("Repositorio: github.com/NopAngel/bear", cursor_y++, GRAY_TXT);
    }else if (strcmp(input_buffer, "welcome") == 0 || strcmp(input_buffer, "splash") == 0) {
        k_clear_screen();
        W_MSG();
    }else if (strncmp(input_buffer, "mkdir ", 6) == 0) {
        const char *dirname = input_buffer + 6;
        cursor_y = 20;

        mkdir(dirname);
    }

    else if (strncmp(input_buffer, "touch ", 6) == 0) {
        const char *filename = input_buffer + 6;
        cursor_y = 20;

        touch(filename, "");
    }else if (strcmp(input_buffer, "pwd") == 0) {
        k_printf("*/home/", cursor_y++, GREEN_TXT);
    } else if (strncmp(input_buffer, "man mkdir", 6) == 0) {
        cursor_y = cursor_y + 1;
        k_printf("MKDIR:", cursor_y++, BLUE_TXT);
        k_printf("Este comando nos ayuda para crear una carpeta", cursor_y++, WHITE_TXT);
        k_printf("Solo tienes que poner: mkdir (nombre_del_archivo)", cursor_y++,WHITE_TXT);
    }else if (strncmp(input_buffer, "man touch", 6) == 0) {
        cursor_y = cursor_y + 1;
        k_printf("TOUCH:", cursor_y++, BLUE_TXT);
        k_printf("Este comando nos ayuda para crear un archivo", cursor_y++, WHITE_TXT);
        k_printf("Solo tienes que poner: touch (nombre_del_archivo.su_respectiva_extension)", cursor_y++,WHITE_TXT);
    }else if (strncmp(input_buffer, "man test", 6) == 0) {
        cursor_y = cursor_y + 1;
        k_printf("TEST:", cursor_y++, BLUE_TXT);
        k_printf("Este comando nos ayuda a proba si esta corriendo el KERNEL", cursor_y++, WHITE_TXT);
        k_printf("Correctamente, uso: 'test', es totalmente sin parametros.", cursor_y++,WHITE_TXT);
    }

    else if (strcmp(input_buffer, "ls") == 0) {
        k_clear_screen();
        cursor_y = 20;
        list_items();
    }

    else if (strcmp(input_buffer, "bear") == 0) {
        k_printf("KERNEL PANIC: OH NO!!! Los BEARS han tomado el control (FATAL ERROR, yeah esto es una broma jeje)", cursor_y++, RED_TXT);
    }
     else if (strcmp(input_buffer, "clear") == 0) {
        k_clear_screen();
        cursor_y = 0; 
    }else if (strcmp(input_buffer, "") == 0) {
        k_clear_screen();
        cursor_y = cursor_y + 1;
        
    }
else if (strcmp(input_buffer, "sh") == 0) {
        k_printf("BearSH v1.3", cursor_y++, GREEN_TXT);
        }
     else {
        k_printf("Comando no reconocido.", cursor_y++, RED_TXT); 
    }


    if (cursor_y >= SCREEN_ROWS) {
        scroll_screen(); 
    }


    input_index = 0;
    cursor_x = 0;
}


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








int caps_lock = 0;         
int shift_pressed = 0;     




void keyboard_handler_logged() {
    unsigned char scancode = read_scancode();


    if (scancode == last_scancode ) {
        return;
    }

    last_scancode = scancode;


    if (scancode & 0x80 ) {
      
        scancode &= 0x7F;

     
        if (scancode == 0x2A || scancode == 0x36) { 
            shift_pressed = 0;
        }

        return;
    } else {
       
        if (scancode == 0x2A || scancode == 0x36) { 
            shift_pressed = 1;
            return;
        } else if (scancode == 0x3A) { 
            caps_lock = !caps_lock; 
            return;
        }
    }


    if (scancode < sizeof(scancode_to_ascii)) {
        char ascii = scancode_to_ascii[scancode];

     
        if ((caps_lock || shift_pressed) && ascii >= 'a' && ascii <= 'z') {
            ascii -= 32;
        } else if (shift_pressed && ascii >= '0' && ascii <= '9') {
         
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
                case ',': ascii = ';'; break;
                case '.': ascii = ':'; break;
            }
        }

    
        if (ascii == '\b') { 
            if (input_index > 0) {
                input_index--; 
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
        } else if (ascii == '\n') { 
            process_input_logged(); 
        } else if (ascii) { 
            if (input_index < INPUT_BUFFER_SIZE - 1) { 
                input_buffer[input_index++] = ascii;
                put_char(ascii); 
            }
        }
    }
}

void keyboard_handler() {
    unsigned char scancode = read_scancode();


    if (scancode == last_scancode ) {
        return;
    }

    last_scancode = scancode;

    if (scancode & 0x80 ) {
     
        scancode &= 0x7F;

  
        if (scancode == 0x2A || scancode == 0x36) { 
            shift_pressed = 0;
        }

        return;
    } else {
     
        if (scancode == 0x2A || scancode == 0x36) { 
            shift_pressed = 1;
            return;
        } else if (scancode == 0x3A) { 
            caps_lock = !caps_lock; 
            return;
        }
    }

 
    if (scancode < sizeof(scancode_to_ascii)) {
        char ascii = scancode_to_ascii[scancode];

   
        if ((caps_lock || shift_pressed) && ascii >= 'a' && ascii <= 'z') {
            ascii -= 32;
        } else if (shift_pressed && ascii >= '0' && ascii <= '9') {
   
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
                case ',': ascii = ';'; break;
                case '.': ascii = ':'; break;
            }
        }


        if (ascii == '\b') { 
            if (input_index > 0) {
                input_index--; 
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
        } else if (ascii == '\n') { 
            process_input();
        } else if (ascii) { 
            if (input_index < INPUT_BUFFER_SIZE - 1) {
                input_buffer[input_index++] = ascii;
                put_char(ascii); 
            }
        }
    }
}





void k_main(uint32_t magic, multiboot_info_t *multiboot_info) 
{
    mkdir("scripts");
    mkdir("system");
    touch("IMPORTANT.md", "haha");

    k_clear_screen();


    cursor_x = 0;
    cursor_y = 19; 

    
    sound_init();


    init_shared_memory();

    void *block1 = allocate_shared_memory(512);


    void *block2 = allocate_shared_memory(512);


    free_shared_memory(block1);



    W_MSG();

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
        vidmem[i] = *message;      
        message++;
        i++;
        vidmem[i] = color;         
        i++;
    }

    return 1; 
}


/*

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
}*/

unsigned int k_printf_center(char *message, unsigned int line, unsigned int color) {
    char *vidmem = (char *) 0xb8000;
    unsigned int i = 0;
    unsigned int length = 0;

    
    char *ptr = message;
    while (*ptr != 0) {
        length++;
        ptr++;
    }

    unsigned int padding = (80 - length) / 2;

   
    i = (line * 80 * 2) + (padding * 2);

    
    while (*message != 0) {
        if (*message == '\n') { 
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





/*
*
*
*
*
*		 FOOTER - COMMENTARY FOR DEVELOPERS
*
*
*
*
*
*
*		kernel.c:
*			- The code editor used for the ESET kernel is: badeditor. This editor was created by myself 
*                    (it's a code editor in the terminal), which basically allows you to write much more comfortably and quickly.
*            brings support to:
*
*			- C
*
*			- C++
*
*			- Assembly
*	
*			- SH (Shell Script)
*
*			- Pascal
*
*			- LD/linker script (just the highlight)
*
*
*	It has quite a few things, if you want you can take a look at each of them, it will soon be published on my GitHub,
*                         and it will be open source :)
*	
*/
