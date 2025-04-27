/*
*
*   kernel.c - the main file that run's the entire code ( It is the main one, which calls all the functions )
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
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

int logged;
void k_clear_screen();
#include "fs/k_printf.h"
#include "reboot.h"
#include "include/multiboot.h"
#include "shutdown.h"
#include "include/itoa.h"
#include "cpu/get_cpu_info.h"
#include "include/memory/sharedmemory.h"
#include "include/drivers/vesa/vesa.h"
#include "include/drivers/mouse/mouse.h"







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






void kernel_panic();




/*
void *allocate_shared_memory(unsigned int size);
void free_shared_memory(void *address);
void init_shared_memory();
*/




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

static inline void outl(unsigned short port, unsigned int value) {
    asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

static inline unsigned int inl(unsigned short port) {
    unsigned int value;
    asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port));
    return value;
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

void delay(int time) {
	volatile long count = 1000000 * time;
	while(count--); 
}

void CR_W() {
	k_clear_screen();
	k_printf("[BEAR] Bear packs loading",0, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Bear packs loaded.",0, GREEN_TXT);

	k_printf("[BEAR] Init scripts",1, GREEN_TXT);


	k_printf("[BEAR] APM Manager inited",2, GREEN_TXT);


	k_printf("[BEAR] Terminal preparing",3, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Terminal prepared.",3, GREEN_TXT);


	k_printf("[BEAR] Keyboard port inited",4, GREEN_TXT);
    delay(10);

	k_printf("[BEAR] Sound inited port",5, GREEN_TXT);


	k_printf("[BEAR] VGA Resolution PREPARED",6, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] VGA Resolution PREPARED",6, GREEN_TXT);


	k_printf("[BEAR] Keyboard Scanned loading",7, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Keyboard Scanned loaded.",7, GREEN_TXT);


	k_printf("[BEAR] Commands PREPARING",8, GREEN_TXT);
    delay(10);
    k_printf("[BEAR] Commands PREPARED..",8, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Drivers PREPARING..",9, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Drivers PREPARED..",10, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Disk method PREPARING",11, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Disk method PREPARED..",12, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] PCI Devices PREPARING",13, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] PCI Devices PREPARED..",14, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Colors loading",15, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Colors loaded..",16, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Optimization PREPARING",17, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Optimization PREPARED..",18, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Itoa PREPARING",19, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] Itoa PREPARED..",20, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] SOUND DRVIER PREPARED",21, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] SOUND DRIVER PREPARING..",22, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] INFORMATION PREPARING",23, GREEN_TXT);
    delay(10);

    k_printf("[BEAR] INFORMATION PREPARED..",24, GREEN_TXT);
    delay(10);


	k_printf("-----------------------------------",25, WHITE_TXT);
    k_clear_screen();
	delay(200);
	k_clear_screen();
    k_printf_center("BearOS starting - Author: NopAngel", 12, ORANGE_TXT);
    delay(300);
}

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC





void LOGIN_W() {
    k_clear_screen();
    k_printf_center("****************************", 9, WHITE_TXT);
    k_printf_center("| BearOS logged screen     |", 10, WHITE_TXT);
    k_printf_center("| Username and Password    |", 11, WHITE_TXT);
    k_printf_center("****************************", 12, WHITE_TXT);
}

void W_MSG() {
    k_clear_screen();
     k_printf_center("+", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+---", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+----", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+------", 0, ORANGE_TXT); 
    delay(5);

    k_printf_center("+-------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+---------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+----------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+------------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-------------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------------", 0, ORANGE_TXT); 
    delay(5);

    k_printf_center("+---------------",0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+----------------",0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----------------",0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----------------",0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+------------------",0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-------------------",0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------------------", 0, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------------------+",0, ORANGE_TXT);
    k_printf_center("B", 1, WHITE_TXT); 
    delay(5);
    k_printf_center("Be", 1, WHITE_TXT); 
    delay(5);
    k_printf_center("Bea", 1, WHITE_TXT); 
    delay(5);
    k_printf_center("Bear", 1, WHITE_TXT); 
    delay(5);
    k_printf_center("BearO", 1, WHITE_TXT); 
    delay(5);
    k_printf_center("BearOS", 1, WHITE_TXT);  
    delay(5);
    k_printf_center("+", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+---", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+----", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+------", 2, ORANGE_TXT); 
    delay(5);

    k_printf_center("+-------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+---------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+----------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------------", 2, ORANGE_TXT); 
    delay(5);

    k_printf_center("+---------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+----------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-----------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+------------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+-------------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------------------", 2, ORANGE_TXT); 
    delay(5);
    k_printf_center("+--------------------+", 2, ORANGE_TXT); 





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
        k_printf("Error: Color not found.\n", 0, RED_TXT);
        return;
    }


    char *vidmem = (char *)0xb8000;
    for (int i = 0; i < SCREEN_ROWS * SCREEN_COLUMNS; i++) {
        vidmem[i * 2 + 1] = current_bg_color; 
    }
}







void W_MSG();


int mkdir(const char *dirname) {

    if (directory_count >= MAX_DIRECTORIES) {
        k_printf("Error: No more directories can be created.\n", 0, RED_TXT);
        return -1;
    }


    if (strlen(dirname) >= MAX_NAME_LENGTH) {
        k_printf("Error: The name is long.\n", 0, RED_TXT);
        return -1;
    }

    for (unsigned int i = 0; i < directory_count; i++) {
        if (strcmp(directory_table[i].name, dirname) == 0) {
            k_printf("Error: The directory already exists.\n", 0, RED_TXT);
            return -1;
        }
    }

 
    strcpy(directory_table[directory_count].name, dirname); 
    directory_table[directory_count].start_block = directory_count * 16; 
    directory_table[directory_count].size = 1; 
    directory_count++; 

    k_printf("Directory's created: ", 0, GREEN_TXT);
    k_printf_no_newline(dirname, 0, WHITE_TXT);
    k_printf_no_newline("\n", 0, WHITE_TXT);

    return 0;
}

void show_file_content(const char *filename) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) { 
            k_printf_no_newline(filename, 0, WHITE_TXT); 
            k_printf_no_newline(file_table[i].content, 0, WHITE_TXT); 
            return; 
        }
    }
   
    k_printf("File not found", 0, RED_TXT);
}


void list_items() {
    int cursor_y = 0;


    if (directory_count > 0) {
        k_printf("Directory's:\n", cursor_y++, BLUE_TXT);
        for (unsigned int i = 0; i < directory_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            k_printf_no_newline(directory_table[i].name, cursor_y++, WHITE_TXT);
        }
    }
    cursor_y = cursor_y + 2;


    if (file_count > 0) {
        k_printf("File's:\n", cursor_y++, GREEN_TXT);
        for (unsigned int i = 0; i < file_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            k_printf_no_newline(file_table[i].name, cursor_y++, WHITE_TXT);

        }
    }


    if (directory_count == 0 && file_count == 0) {
        k_printf("No content.\n", 1, WHITE_TXT);

    }
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

























unsigned int get_ram_size() {
    unsigned int ram_size = 0x100000; 
    return ram_size / 1024; 
}

unsigned int get_disk_usage() {
    unsigned char usage;
    __asm__ __volatile__(
        "xor %%dx, %%dx\n\t"     
        "mov $0x1F0, %%dx\n\t"   
        "in %%dx, %%al\n\t"    
        "mov %%al, %0\n\t"     
        : "=r"(usage)
        :
        : "dx", "al"
    );
    return (unsigned int)usage * 512; 
}


unsigned int safe_mod(unsigned int dividend, unsigned int divisor) {
    return dividend - (divisor * (dividend / divisor));
}



void display_stats() {
    char buffer[32];
    unsigned int cpu_cycles = get_cpu_cycles();
    unsigned int ram_usage = get_ram_size(); 
    unsigned int disk_usage = get_disk_usage();
    k_printf("MORE INFORMATION                                                                          ", cursor_y++, GREEN_BG_BLACK);

    k_printf("CPU Cycles:", cursor_y++, ORANGE_TXT);
    itoa(cpu_cycles, buffer, 10);
    k_printf(buffer, cursor_y++, AQUA_TXT);

    k_printf("RAM Usage (MB):", cursor_y++, GREEN_TXT);
    itoa(ram_usage, buffer, 10);
    k_printf(buffer, cursor_y++, AQUA_TXT);

    k_printf("Disk Usage (MB):", cursor_y++, BLUE_TXT);
    itoa(disk_usage, buffer, 10);
    k_printf(buffer, cursor_y++, AQUA_TXT);

    k_printf_center("Writting for exit", 21, WHITE_TXT);
}

void process_input_logged() {
    input_buffer[input_index] = '\0'; 

    if (strcmp(input_buffer, "root123") == 0) {
        cursor_y++;
        logged = 1;
        W_MSG();

    } else {
        cursor_y++;
        k_printf("Password incorrect ",cursor_y++, RED_TXT);
    }

    cursor_x = 0;
    input_index = 0;

}


void process_input() {
    input_buffer[input_index] = '\0'; 


    if (strcmp(input_buffer, "test") == 0) {
        k_printf("Hello, World!", cursor_y, GREEN_TXT); 
        cursor_y++;
    }

    
else if (strcmp(input_buffer, "shutdown now") == 0) {

    


    k_clear_screen();
    set_background_color("blue");
    k_printf_center("                                              ", 10,  WHITE_BG_BLACK);
    k_printf_center("              Turning off computer.           ", 11,  WHITE_BG_BLACK);
    k_printf_center("                                              ", 12,  WHITE_BG_BLACK);



    delay(500);


   
  asm volatile (
        "movl $0x5307, %eax \n"
        "movl $0x0001, %ebx \n"
        "movl $0x0003, %ecx \n"
        "int $0x15"
    );
}





  

    else if (strcmp(input_buffer, "stats") == 0) {
    	k_clear_screen();
    	cursor_y = 0;
        display_stats();
    	
    }

    else if (strcmp(input_buffer, "bearfetch") == 0) {
        k_clear_screen();
        k_printf_center("BEAR OS", 4, ORANGE_TXT);
        k_printf_center("------------------------------------", 5, ORANGE_TXT);
        k_printf_center(" Author: NopAngel", 6, WHITE_TXT);
        k_printf_center(" Repository: github.com/NopAngel/bear", 7, WHITE_TXT);
        k_printf_center(" BearSH: 1.3", 8, WHITE_TXT);
        k_printf_center(" LICENSE: APACHE 2.0", 8, WHITE_TXT);
        k_printf_center("------------------------------------", 9, ORANGE_TXT);

        
    }
    

    
    else if (strcmp(input_buffer, "about") == 0) {
        k_clear_screen();
        cursor_y = 0;
        k_printf_center("about", cursor_y++, WHITE_TXT);
        k_printf_center("bear OS", cursor_y++, WHITE_TXT);
        k_printf_center("The Bear operating system.", cursor_y++, WHITE_TXT);
        k_printf_center("v2", cursor_y++, BLUE_TXT);
        k_printf_center("Copyright @ 2024-2025", cursor_y++, WHITE_TXT);
        k_printf_center("NopAngel & contributors.", cursor_y++, GRAY_TXT);
    
    }

    else if (strncmp(input_buffer, "print ", 6) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 6;
        k_printf(value, cursor_y++, WHITE_TXT);
    }

    else if (strncmp(input_buffer, "mkdir ", 6) == 0) {
        const char *dirname = input_buffer + 6;
        cursor_y = cursor_y + 1;

        mkdir(dirname);
    }
    else if (strncmp(input_buffer, "touch ", 6) == 0) {
        const char *filename = input_buffer + 6;
        cursor_y = 20;

        touch(filename, "");
    }
    else if (strcmp(input_buffer, "ls") == 0) {
        k_clear_screen();
        cursor_y = 20;
        list_items();
    }
    





     else if (strncmp(input_buffer, "setbg/", 6U) == 0) {
    const char *color_name = input_buffer + 6; 
    set_background_color(color_name);         
}
else if (strcmp(input_buffer, "repo") == 0) {
        k_printf("Repositorio: github.com/NopAngel/bear", cursor_y++, GRAY_TXT);
    }else if (strcmp(input_buffer, "welcome") == 0 || strcmp(input_buffer, "splash") == 0) {
        k_clear_screen();
        W_MSG();
    }

else if (strcmp(input_buffer, "pwd") == 0) {
        k_printf("*/home/", cursor_y++, GREEN_TXT);
    } 

    

   
     else if (strcmp(input_buffer, "clear") == 0) {
        k_clear_screen();
        cursor_y = 0; 
    }
else if (strcmp(input_buffer, "sh") == 0) {
        k_printf("BearSH v1.4", cursor_y++, GREEN_TXT);
        }
     else {
        k_printf("Command not found.", cursor_y++, RED_TXT); 
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


/*

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
        }  else if (ascii) { 
            if (input_index < INPUT_BUFFER_SIZE - 1) {
                input_buffer[input_index++] = ascii;
                put_char(ascii); 
            }
        }
    }
}*/






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
        }  else if (ascii) { 
            if (input_index < INPUT_BUFFER_SIZE - 1) {
                input_buffer[input_index++] = ascii;
                put_char(ascii); 
            }
        }
    }

}









static inline unsigned char inb(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}


void keyboard_handler() {
volatile int ctrl_pressed = 0;

    unsigned char scancode = read_scancode();
  unsigned char scancode1 = inb(0x60);
  if (scancode1 == 0x1D) { // Ctrl pressed
        ctrl_pressed = 1;
    } else if (scancode1 == 0x9D) { // Ctrl down
        ctrl_pressed = 0;
    } else if (scancode1 == 0x26 && ctrl_pressed) { // ctrl + l pressed
        k_clear_screen();
    }

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

	CR_W();


    cursor_x = 0;
    cursor_y = 19; 



//delete_inode(&sb, inodes, new_inode->inode_number);

    

    sound_init();


    init_shared_memory();

    void *block1 = allocate_shared_memory(512);


    void *block2 = allocate_shared_memory(512);


    free_shared_memory(block1);



    LOGIN_W();
    //delay(700);

    //W_MSG();




    while (1) {
   
        if(logged == 1) {
         keyboard_handler();

        } else if(logged == 0)  {
         keyboard_handler_logged();

    }



}


}

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
