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
#include "fs/k_printf_noline.h"
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

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

unsigned char read_cmos(unsigned char reg) {
    asm volatile (
        "mov %1, %%dx\n\t"
        "mov %2, %%al\n\t"
        "out %%al, %%dx\n\t"
        "mov %3, %%dx\n\t"
        "in %%dx, %%al\n\t"
        : "=a" (reg)
        : "i" (CMOS_ADDRESS), "r" (reg), "i" (CMOS_DATA)
        : "dx"
    );
    return reg;
}



void get_time() {
    unsigned char hours = read_cmos(0x04);
    unsigned char minutes = read_cmos(0x02);
    unsigned char seconds = read_cmos(0x00);
    char time_str[3]; 
    time_str[0] = (hours / 10) + '0'; 
    time_str[1] = (hours % 10) + '0'; 
    time_str[2] = '\0'; 

    char seconds_str[3]; 
    seconds_str[0] = (seconds / 10) + '0'; 
    seconds_str[1] = (seconds % 10) + '0'; 
    seconds_str[2] = '\0';

    char minutes_str[3]; 
minutes_str[0] = (minutes / 10) + '0'; 
minutes_str[1] = (minutes % 10) + '0'; 
minutes_str[2] = '\0';

    k_clear_screen();
    k_printf(time_str, GREEN_TXT, 0);
    k_printf(minutes_str, GREEN_TXT, 1);
    k_printf(seconds_str, GREEN_TXT, 2); // THIS IS A BUG :,V
}














#define MAX_PROCESSES 5 


struct ProcessInfo {
    unsigned int pid;
    char name[32];
    unsigned int cpu_usage;
    unsigned int memory_usage;
};

struct ProcessInfo process_table[MAX_PROCESSES];


int convert_to_string(char *buffer, unsigned int value) {
    char temp[10];
    int i = 0, length = 0;

    do {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    while (i > 0) {
        *buffer++ = temp[--i];
        length++;
    }

    return length;
}


int copy_string(char *dest, const char *src) {
    int length = 0;
    while (*src) {
        *dest++ = *src++;
        length++;
    }
    *dest = '\0';
    return length;
}

void sniff() {
    int i;
    unsigned int line = 5;
    unsigned int color = 0x07;
    k_clear_screen();
    k_printf("Sniff - Command", 0, GREEN_TXT);


    for (i = 0; i < MAX_PROCESSES; i++) {
        if (process_table[i].pid > 0) { 
            char buffer[128];
            char *ptr = buffer;

            ptr += convert_to_string(ptr, process_table[i].pid);
            *(ptr++) = ' ';
            ptr += copy_string(ptr, process_table[i].name);
            *(ptr++) = ' ';
            ptr += convert_to_string(ptr, process_table[i].cpu_usage);
            *(ptr++) = '%';
            *(ptr++) = ' ';
            ptr += convert_to_string(ptr, process_table[i].memory_usage);
            *(ptr++) = 'K';
            *(ptr++) = 'B';
            *(ptr++) = '\0';

            k_printf(buffer, line++, color);
        }
    }

}







void init_process_table() {
    process_table[0].pid = 1;
    copy_string(process_table[0].name, "KernelTask");
    process_table[0].cpu_usage = 10;
    process_table[0].memory_usage = 512;

    process_table[1].pid = 2;
    copy_string(process_table[1].name, "UserShell");
    process_table[1].cpu_usage = 5;
    process_table[1].memory_usage = 256;
}


















void roar(char *message){
    k_printf(message, 20, BLUE_WHITE_TXT);
}

#define MAX_TRACK_ENTRIES 40  

struct TrackEvent {
    char message[64]; 
    unsigned int timestamp;  
};

struct TrackEvent track_log[MAX_TRACK_ENTRIES];


void track_event(const char *msg, unsigned int timestamp) {
    int i;

    for (i = MAX_TRACK_ENTRIES - 1; i > 0; i--) {
        copy_string(track_log[i].message, track_log[i - 1].message);
        track_log[i].timestamp = track_log[i - 1].timestamp;
    }


    copy_string(track_log[0].message, msg);
    track_log[0].timestamp = timestamp;
}

void track() {
    unsigned int line = 5;
    unsigned int color = 0x07;
    int has_active_processes = 0; 

    k_printf("Track", 1, GREEN_TXT);

    for (int i = 0; i < MAX_TRACK_ENTRIES; i++) {
        if (track_log[i].timestamp != 0) {
            has_active_processes = 1;  
            char buffer[128];
            char *ptr = buffer;

            ptr += copy_string(ptr, track_log[i].message);
            *(ptr++) = ' ';
            ptr += convert_to_string(ptr, track_log[i].timestamp);
            *(ptr++) = '\0';

            k_printf(buffer, line++, color);
        }
    }

    if (!has_active_processes) {
        k_printf("No process is being used", line++, color);
    }

}








void hibernateLight() {

    asm volatile ("pushf");  
    asm volatile ("pushal");   

    asm volatile ("hlt");      


    asm volatile ("popal");    
    asm volatile ("popf");    
}

void hibernate_cozy() {
    k_clear_screen();
    unsigned int color = 0x0E;  
    unsigned int line = 10;

   
    k_printf("Joined mode cozy... ", line++, color);
    k_printf("Save status the system...", line++, color);

    for (int i = 0; i < 3; i++) {
        k_printf(".", line, color);
    }


    asm volatile("hlt");  
}









struct FurTheme {
    unsigned int text_color;
    unsigned int background_color;
    char name[16];
};

struct FurTheme themes[] = {
    {0x07, 0x00, "Classic"},  
    {0x0A, 0x00, "Forest"},  
    {0x0E, 0x00, "Warm"},     
    {0x0C, 0x00, "Wild"},     
};

// Change theme active
void furstyle(unsigned int theme_index) {
    k_clear_screen();
    if (theme_index >= sizeof(themes) / sizeof(struct FurTheme)) {
        k_printf("Theme not found", 5, 0x0C);
        return;
    }

    unsigned int text_color = themes[theme_index].text_color;
    unsigned int bg_color = themes[theme_index].background_color;

    k_printf("Applying theme: ", 6, text_color);
    k_printf(themes[theme_index].name, 7, text_color);

}


int compare_strings(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return 0;
        }
        str1++;
        str2++;
    }
    return (*str1 == *str2);  
}


unsigned int get_theme_index(const char *theme_name) {
    for (unsigned int i = 0; i < sizeof(themes) / sizeof(struct FurTheme); i++) {
        if (compare_strings(theme_name, themes[i].name)) {
            return i; 
        }
    }
    return 0; 
}




struct FurVision {
    unsigned int brightness;
    unsigned int contrast;
    char mode[16];
};

struct FurVision vision_modes[] = {
    {5, 5, "Normal"},   
    {8, 7, "Bright"}, 
    {3, 4, "Night"},  
    {6, 6, "Gentle"}     
};

unsigned int get_vision_index(const char *mode_name) {
    for (unsigned int i = 0; i < sizeof(vision_modes) / sizeof(struct FurVision); i++) {
        if (compare_strings(mode_name, vision_modes[i].mode)) {
            return i;  
        }
    }
    return 0; 
}



void furvision(unsigned int mode_index) {
    if (mode_index >= sizeof(vision_modes) / sizeof(struct FurVision)) {
        k_printf("Mode not found", 5, 0x0C);
        return;
    }

    unsigned int brightness = vision_modes[mode_index].brightness;
    unsigned int contrast = vision_modes[mode_index].contrast;

    k_printf("Adjusting FurVision: ", 6, 0x0E);
    k_printf(vision_modes[mode_index].mode, 7, 0x0E);
}

void denreboot() {
    k_printf("Reset BearOS...", 10, 0x0C);
    k_printf("Save data...", 11, 0x0C);

    for (int i = 0; i < 100000; i++) { asm volatile("nop"); }


    asm volatile (
        "cli;"           
        "movb $0xFE, %al;" 
        "outb %al, $0x64;" 
        "hlt;"             
    );
}

int check_memory_error(unsigned int addr);
void repair_memory(unsigned int addr);





void list_items() {
    int cursor_y = 0;


    if (directory_count > 0) {
        k_printf("Directory's:\n", cursor_y++, BLUE_TXT);
        for (unsigned int i = 0; i < directory_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            (directory_table[i].name, cursor_y++, WHITE_TXT);
        }
    }
    cursor_y = cursor_y + 2;


    if (file_count > 0) {
        k_printf("File's:\n", cursor_y++, GREEN_TXT);
        for (unsigned int i = 0; i < file_count; i++) {
            ("  - ", cursor_y++, WHITE_TXT);
            (file_table[i].name, cursor_y++, WHITE_TXT);

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
    } else if(strcmp(input_buffer, "track") == 0) {
        k_clear_screen();
            track_event("Kernel init", 1);
    track_event("Load modules", 2);
    track();
    } else if (strcmp(input_buffer, "hibernate -light") == 0) {
        hibernateLight(); // Congalate pc data
    } else if (strcmp(input_buffer, "hibernate -cozy") == 0) {
        hibernate_cozy(); // Save PC data
    } else if (strncmp(input_buffer, "furstyle ", 9) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 9;
        furstyle(get_theme_index(value));
    }else if (strncmp(input_buffer, "furvision ", 10) == 0) {
        cursor_y = cursor_y + 1;
        const char *value = input_buffer + 9;
        furvision(get_vision_index(value));

    } else if (strcmp(input_buffer, "denreboot") == 0) {
        denreboot();
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

else if (strcmp(input_buffer, "sniff") == 0) {

   init_process_table();  
    sniff();               

}





  

    else if (strcmp(input_buffer, "stats") == 0) {
    	k_clear_screen();
    	cursor_y = 0;
        display_stats();
    	
    } else if(strcmp(input_buffer, "time") == 0) {
        get_time();
    }

    else if (strcmp(input_buffer, "bearfetch") == 0) {
        k_clear_screen();
        k_printf_center("root@bearOS", 4, ORANGE_TXT);
        k_printf_center("------------------------------------", 5, ORANGE_TXT);
        k_printf_center("Kernel: Bear Operating System v2.2.3", 6, WHITE_TXT);
        k_printf_center("Swap: Disabled", 7, WHITE_TXT);
        k_printf_center("Locale: C.UTF-8", 8, WHITE_TXT);
        k_printf_center("Terminal: bearSH (integrated - 800x600)", 9, WHITE_TXT);
        k_printf_center("------------------------------------", 10, ORANGE_TXT);

        
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





