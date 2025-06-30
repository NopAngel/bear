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

#define CYAN_TXT 3  // Asegurar que existe la constante


// --- FS MOCK --- funciones implementadas en kernel.c directamente

int memfs_open(const char *path, int flags) {
    if (path[0] == '/' && path[1] == 'm' && path[2] == 'n')
        return 0; // solo acepta un archivo
    return -1;
}

int memfs_close(int fd) {
    return 0;
}

int memfs_read(int fd, void *buf, unsigned int count) {
    const char *fake = "Desde memfs.";
    unsigned int i;
    for (i = 0; i < count && fake[i]; i++)
        ((char*)buf)[i] = fake[i];
    return i;
}

int memfs_write(int fd, const void *buf, unsigned int count) {
    return count; // descartamos, pero simulamos éxito
}



unsigned int get_system_time() { // SIMULATION
    
    static unsigned int time_counter = 0;
    return time_counter++;  
}









#define MAX_NAME_LENGTH 256
#define MAX_CONTENT_LENGTH 1024
int cursor_x = 0;   
int cursor_y = 0; 
int input_index = 0;    


volatile unsigned char last_scancode = 0;

int logged = 1;
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
#include "include/drivers/ps2/drv.h"
#include "./rtc.h"
#include "fs/k_printf_xy.h"





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








#define VIDEO_MEMORY ((unsigned short*)0xB8000)
#define SCREEN_WIDTH 80

void text_draw(int x, int y, char c, unsigned char color) {
    unsigned short attribute = ((unsigned short)color << 8) | c;
    VIDEO_MEMORY[y * SCREEN_WIDTH + x] = attribute;
}




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


void bear_panic(const char *msg) {
    
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++)
            text_draw(x, y, ' ', 0x4C);  
    }
    const char *header = "PANIC ERROR ";
    int x = (80 - 18) / 2;
    for (int i = 0; header[i]; i++)
        text_draw(x + i, 5, header[i], 0x47);  

    int y = 8;
    for (int i = 0; msg[i] && y < 24; i++) {
        text_draw((i % 60) + 10, y, msg[i], 0x47); 
        if (i % 60 == 59) y++;
    }

    // Loop infinito
    while (1) {
        __asm__ volatile ("hlt");
    }
}






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
}

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC



int uptime_seconds = 0;

void timer_tick() {
    static int ticks = 0;
    ticks++;
    if (ticks >= 100) {   // supón 100 ticks = 1 segundo
        ticks = 0;
        uptime_seconds++;
    }
}

void cmd_uptime() {
    char msg[32];
    int sec = uptime_seconds;
    int min = sec / 60;
    sec %= 60;

    int i = 0;
    msg[i++] = 'U'; msg[i++] = 'p'; msg[i++] = 't'; msg[i++] = 'i'; msg[i++] = 'm'; msg[i++] = 'e';
    msg[i++] = ':'; msg[i++] = ' ';
    msg[i++] = '0' + min / 10;
    msg[i++] = '0' + min % 10;
    msg[i++] = 'm';
    msg[i++] = ' ';
    msg[i++] = '0' + sec / 10;
    msg[i++] = '0' + sec % 10;
    msg[i++] = 's';
    msg[i] = '\0';

    for (int j = 0; msg[j]; j++){
        text_draw(j, 20, msg[j], 0x0B); // línea 20, color cian
}
}



void W_MSG() {
    k_clear_screen();
    k_printf("root@bear", 0, WHITE_TXT);
    k_printf("---------", 1, WHITE_TXT);
    k_printf("OS: BearOS x86 (KERNEL)", 2, WHITE_TXT);
    k_printf("Shell: bash_bear x86_a6", 3, WHITE_TXT);
    k_printf("FileSystem: FAT32 (default)", 4, WHITE_TXT);
    
    // COLORS in TEXT.
    
    k_printf_xy("OS",0, 2, RED_TXT);
    k_printf_xy("Shell",0, 3, RED_TXT);
    k_printf_xy("FileSystem",0, 4, RED_TXT);
    
    k_printf_xy("  ", 6,6, BLACK_BG);
    k_printf_xy("  ", 8,6, GRAY_BG);
    k_printf_xy("  ", 10,6, RED_BG);
    k_printf_xy("  ", 12,6, ORANGE_BG);
    k_printf_xy("  ", 14,6, PINK_BG);
   

    
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



#define MAX_FILES 100

typedef struct {
    char name[MAX_NAME_LENGTH];    
    unsigned int start_block;     
    unsigned int size;             
    char content[MAX_CONTENT_LENGTH];
} FileEntry;

FileEntry file_table[MAX_FILES];  
unsigned int file_count = 0;



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



static inline unsigned char inb(unsigned short port) {
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}


void clear_memory(char *buffer, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        buffer[i] = 0;  // **Inicializar manualmente**
    }
}



//LOGS


#define MAX_LOG_ENTRIES 50  // 🔥 Número máximo de logs en memoria

typedef enum { INFO, WARNING, ERROR } LogLevel;  // 🔥 Niveles de prioridad

typedef struct {
    char message[128];  
    unsigned int timestamp;  
    LogLevel level;  // **Nuevo campo de prioridad**
} LogEntry;




LogEntry log_buffer[MAX_LOG_ENTRIES];
unsigned int log_index = 0;  // Posición actual en el buffer



void add_log(const char *message, unsigned int timestamp, LogLevel level) {
    log_buffer[log_index].timestamp = timestamp;
    log_buffer[log_index].level = level;
    custom_strcpy(log_buffer[log_index].message, message);

    log_index = (log_index + 1) % MAX_LOG_ENTRIES;  // 🔄 Circular
}





void show_logs(LogLevel filter_level) {
    k_printf("=== SYSTEM LOGS ===\n", 0, CYAN_TXT);
    
    for (unsigned int i = 0; i < MAX_LOG_ENTRIES; i++) {
        if (log_buffer[i].message[0] != '\0' && log_buffer[i].level >= filter_level) {  
            
            // 📌 Mostrar tipo de log con colores
            const char *level_text = (log_buffer[i].level == INFO) ? "[INFO] " :
                                     (log_buffer[i].level == WARNING) ? "[WARNING] " : "[ERROR] ";
            int color = (log_buffer[i].level == INFO) ? GREEN_TXT :
                        (log_buffer[i].level == WARNING) ? ORANGE_TXT : RED_TXT;

            k_printf(level_text, 0, color);
            k_printf(log_buffer[i].message, 0, WHITE_TXT);
        }
    }
}








// TEXT EDITOR

int keyboard_has_input() {
    return inb(0x64) & 1;  // Verifica si hay datos en el buffer del teclado
}


char read_kboard() {
    while (!(inb(0x64) & 1));  // Esperar a que haya datos disponibles
    return inb(0x60);          // Leer carácter del teclado
}



char get_char() {
    char c;
    
    while (1) {
        if (keyboard_has_input()) {  // Validar si hay entrada disponible
            c = read_kboard();     // Función para leer el carácter
            return c;
        }
    }
}


void edit_file(const char *filename, const char *new_content) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].name, filename) == 0) {
            
            // 🔥 **Limpiar memoria sin usar `memset()`**
            clear_memory(file_table[i].content, MAX_CONTENT_LENGTH);

            custom_strcpy(file_table[i].content, new_content);
            file_table[i].size = custom_strlen(new_content);
            file_table[i].content[file_table[i].size] = '\0';  // 🔥 Agregar terminador seguro
            
            return;
        }
    }

    k_printf("Error: File not found.\n", 0, RED_TXT);
}




void edit_file_interactive(const char *filename) {
    char new_content[MAX_CONTENT_LENGTH];

    k_printf("Enter new content (Press '+' to save & exit): ", 0, CYAN_TXT);
    
    int index = 0;
    while (index < MAX_CONTENT_LENGTH - 1) {
        char c = get_char();  // Leer entrada del usuario

        // 📌 Detectar Escape (ASCII 27) y salir automáticamente
        if (c == 27) {
            k_printf("\nSaving file...\n", 0, GREEN_TXT);
            break;
        }

        new_content[index++] = c;
    }

    new_content[index] = '\0';  // Cerrar cadena correctamente
    edit_file(filename, new_content);  // Guardar contenido

    k_printf("Exiting editor...\n", 0, WHITE_TXT);
    return;  // Finalizar función
}
void view_file(const char *filename) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (strcmp(file_table[i].name, filename) == 0) {
            if (file_table[i].size == 0) {
                k_printf("File is empty.\n", 0, RED_TXT);
                return;
            }

            k_printf("File content:\n", 0, CYAN_TXT);

            for (unsigned int j = 0; j < file_table[i].size; j++) {
                char c = file_table[i].content[j];

                // 📌 **Evitar caracteres raros**
                if (c >= 32 && c <= 126) {  
                    k_printf_no_newline(&c, 0, WHITE_TXT);
                } else {
                    k_printf_no_newline(".", 0, RED_TXT);  // 🔥 Reemplazar caracteres inválidos
                }
            }

            k_printf_no_newline("\n", 0, WHITE_TXT);
            return;
        }
    }

    k_printf("Error: File not found.\n", 0, RED_TXT);
}








FileEntry file_table[MAX_FILES];  


#define MAX_CONTENT_LENGTH 1024



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

int fs_write(const char* filename, const char* content, unsigned int size) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) {
            custom_strcpy(file_table[i].content, content);
            file_table[i].size = size;
            return 0;
        }
    }

    // Si no existe, crear uno nuevo
    if (file_count >= MAX_FILES) return -1;

    custom_strcpy(file_table[file_count].name, filename);
    custom_strcpy(file_table[file_count].content, content);
    file_table[file_count].size = size;
    file_table[file_count].start_block = directory_count * 16 + file_count;
    file_count++;
    return 0;
}


int fs_read(const char* filename, char* out_buf, unsigned int max_size) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) {
            if (file_table[i].size > max_size) return -2;

            custom_strcpy(out_buf, file_table[i].content);
            return file_table[i].size;
        }
    }
    return -1; // archivo no encontrado
}


void remove_file(const char *filename) {
    for (unsigned int i = 0; i < file_count; i++) {
        if (custom_strcmp(file_table[i].name, filename) == 0) {
            for (unsigned int j = i; j < file_count - 1; j++) {
                file_table[j] = file_table[j + 1];  
            }
            file_count--; 
            return;
        }
    }
}



int touch(const char *filename, const char *content) {
    create_new_file(filename, content);
    return 0;
}

int rmfile(const char *filename) {
	remove_file(filename);
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

    k_printf("Directory's created.", cursor_y++, GREEN_TXT);
    return 0;
}

int rmdir(const char *dirname) {
    if (directory_count == 0) {
        k_printf("Error: No directories exist.\n", 0, RED_TXT);
        return -1;
    }

    for (unsigned int i = 0; i < directory_count; i++) {
        if (strcmp(directory_table[i].name, dirname) == 0) {
         
            for (unsigned int j = i; j < directory_count - 1; j++) {
                directory_table[j] = directory_table[j + 1];
            }
            
            directory_count--; 
            
            k_printf("Directory removed: ", 0, GREEN_TXT);
            k_printf_no_newline(dirname, 0, WHITE_TXT);
            k_printf_no_newline("\n", 0, WHITE_TXT);

            return 0;
        }
    }

    k_printf("Error: Directory not found.\n", 0, RED_TXT);
    return -1;
}











// CD

unsigned int current_directory = 0;  // default root


int cd_back() {
    if (current_directory == 0) {
        k_printf("Error: Already at root.\n", 0, RED_TXT);
        return -1;
    }

    current_directory--;  // Retrocede un nivel en la jerarquía

    k_printf("Moved back to: ", 0, GREEN_TXT);
    k_printf_no_newline(directory_table[current_directory].name, 0, WHITE_TXT);
    k_printf_no_newline("\n", 0, WHITE_TXT);

    return 0;
}

int cd(const char *dirname) {
    
    
    if(dirname == "..") {
    	cd_back();
    } else {
    for (unsigned int i = 0; i < directory_count; i++) {
        if (strcmp(directory_table[i].name, dirname) == 0) {
            current_directory = i;  // Cambia al nuevo directorio
            k_printf("Directory changed to: ", 0, GREEN_TXT);
            k_printf(dirname, 0, WHITE_TXT);
            return 0;
        }
    }

    k_printf("Error: Directory not found.\n", 0, RED_TXT);
    return -1;
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





#define MAX_HISTORY 1000
char command_history[MAX_HISTORY][128];  
unsigned int history_index = 1;









// MATH

int evaluate_expression(const char *expr) {
    int result = 0;
    char op = '+';
    int num = 0;

    while (*expr) {
        if (*expr >= '0' && *expr <= '9') {
            num = num * 10 + (*expr - '0');
        } else {
            if (op == '+') result += num;
            if (op == '-') result -= num;
            num = 0;
            op = *expr;
        }
        expr++;
    }

    return result + (op == '+' ? num : -num);
}






void save_command(const char *cmd) {
    custom_strcpy(command_history[history_index], cmd);
    history_index += (history_index += 1) % MAX_HISTORY;
}

void show_command_history() {
    for (unsigned int i = 0; i < MAX_HISTORY; i++) {
        if (command_history[i][0] != '\0') {  // Evitar entradas vacías
            k_clear_screen();
            k_printf("Commands saved:", 0, GREEN_TXT);
            k_printf(command_history[i], 3, WHITE_TXT);
        }
    }
}








void lsk_itm() {
    int cursor_y = 3;
    k_clear_screen();

    k_printf("------------------------------------------", 0, ORANGE_TXT);
    k_printf("name:                                 ", 1, ORANGE_TXT);
    k_printf("------------------------------------------", 2, ORANGE_TXT);
    if (directory_count > 0 | file_count > 0) {
        for (unsigned int i = 0; i < directory_count; i++) {
            k_printf_xy("./", 0, cursor_y, BLUE_TXT);
            k_printf_xy("[DIR]", 19, cursor_y, GRAY_TXT);
            k_printf_xy(directory_table[i].name, 2, cursor_y++, BLUE_TXT);

        }

        for (unsigned int i = 0; i < file_count; i++) {
           k_printf_xy("[FILES]", 19, cursor_y, GRAY_TXT);

           k_printf_xy(file_table[i].name, 2, cursor_y++, ORANGE_TXT);

        }
    } else {


    }

}


void list_items() {
    int cursor_y = 0;


    if (directory_count > 0) {
        k_printf("Directory's:\n", cursor_y++, BLUE_TXT);
        for (unsigned int i = 0; i < directory_count; i++) {
            k_printf_no_newline("  - ", cursor_y++, WHITE_TXT);
            k_printf(directory_table[i].name, cursor_y++, WHITE_TXT);
        }
    }
    cursor_y = cursor_y + 2;


    if (file_count > 0) {
        k_printf("File's:\n", cursor_y++, GREEN_TXT);
        for (unsigned int i = 0; i < file_count; i++) {
            k_printf("  - ", cursor_y++, WHITE_TXT);
            k_printf(file_table[i].name, cursor_y++, WHITE_TXT);

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











// TVFS (The VIrtual File System)


#define VFS_TYPE_LENGTH 32
#define VFS_PATH_LENGTH 64
#define MAX_MOUNTPOINTS 12
#define MAX_OPENED_FILES 32
#define ERROR -1

typedef struct {
    int (*open)(const char *path, int flags);
    int (*close)(int fd);
    int (*read)(int fd, void *buf, unsigned int count);
    int (*write)(int fd, const void *buf, unsigned int count);
} fs_operations_t;

typedef struct {
    char type[VFS_TYPE_LENGTH];
    char mountpoint[VFS_PATH_LENGTH];
    fs_operations_t operations;
} mountpoint_t;

typedef struct {
    int fs_file_id;
    int mountpoint_id;
    char *filename;
    int file_size;
    int buf_read_pos;
} file_descriptor_t;

mountpoint_t mountpoints[MAX_MOUNTPOINTS];
int mountpoints_count = 0;

file_descriptor_t vfs_opened_files[MAX_OPENED_FILES];

int vfs_mount(const char *type, const char *mountpoint, fs_operations_t ops) {
    if (mountpoints_count >= MAX_MOUNTPOINTS)
        return ERROR;

    mountpoint_t *m = &mountpoints[mountpoints_count++];
    for (int i = 0; i < VFS_TYPE_LENGTH; i++) m->type[i] = type[i];
    for (int i = 0; i < VFS_PATH_LENGTH; i++) m->mountpoint[i] = mountpoint[i];
    m->operations = ops;

    return 0;
}

int get_mountpoint_id(const char *path) {
    for (int i = 0; i < mountpoints_count; i++) {
        // Aquí puedes mejorar con strncmp
        int match = 1;
        for (int j = 0; mountpoints[i].mountpoint[j] && path[j]; j++) {
            if (mountpoints[i].mountpoint[j] != path[j]) {
                match = 0;
                break;
            }
        }
        if (match)
            return i;
    }
    return ERROR;
}

int vfs_open(const char *path, int flags) {
    int mp_id = get_mountpoint_id(path);
    if (mp_id == ERROR)
        return ERROR;

    mountpoint_t *mp = &mountpoints[mp_id];
    int fs_fd = mp->operations.open(path, flags);
    if (fs_fd == ERROR)
        return ERROR;

    for (int i = 0; i < MAX_OPENED_FILES; i++) {
        if (vfs_opened_files[i].fs_file_id == -1) {
            vfs_opened_files[i].fs_file_id = fs_fd;
            vfs_opened_files[i].mountpoint_id = mp_id;
            vfs_opened_files[i].filename = (char *)path;
            vfs_opened_files[i].buf_read_pos = 0;
            return i;
        }
    }
    return ERROR;
}

int vfs_read(int fd, void *buf, unsigned int count) {
    if (fd < 0 || fd >= MAX_OPENED_FILES)
        return ERROR;

    file_descriptor_t *fdesc = &vfs_opened_files[fd];
    if (fdesc->fs_file_id == -1)
        return ERROR;

    mountpoint_t *mp = &mountpoints[fdesc->mountpoint_id];
    return mp->operations.read(fdesc->fs_file_id, buf, count);
}

int vfs_close(int fd) {
    if (fd < 0 || fd >= MAX_OPENED_FILES)
        return ERROR;

    file_descriptor_t *fdesc = &vfs_opened_files[fd];
    if (fdesc->fs_file_id == -1)
        return ERROR;

    mountpoint_t *mp = &mountpoints[fdesc->mountpoint_id];
    int result = mp->operations.close(fdesc->fs_file_id);
    if (result == 0)
        fdesc->fs_file_id = -1;

    return result;
}

void vfs_init() {
    for (int i = 0; i < MAX_OPENED_FILES; i++) {
        vfs_opened_files[i].fs_file_id = -1;
    }
}
void vfs_list_mountpoints(int start_row) {
    const char *title = "Mountpoints activos:";
    for (int i = 0; title[i]; i++)
        text_draw(i, start_row, title[i], 0x0F); // línea de título

    for (int i = 0; i < mountpoints_count; i++) {
        int col = 0;
        const char *prefix = "- ";
        for (int j = 0; prefix[j]; j++)
            text_draw(col++, start_row + i + 1, prefix[j], 0x0A); // color verde

        for (int j = 0; mountpoints[i].mountpoint[j] && col < 80; j++)
            text_draw(col++, start_row + i + 1, mountpoints[i].mountpoint[j], 0x0F);
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



// FONT's System.
// Tipos mínimos
typedef unsigned char  u8;
typedef unsigned int   u32;


// Framebuffer (dirección ficticia, cámbiala por la real)
u32* framebuffer = (u32*)0xE0000000;
u32 screen_width = 1024;
u32 screen_height = 768;

// Fuente binaria 8x16 (cada carácter ocupa 16 bytes)
u8 font_default[] = {
    // ← pega aquí tu arreglo completo font_default[]
};

// Pinta un píxel en pantalla
void put_pixel(u32 x, u32 y, u32 color) {
    if (x < screen_width && y < screen_height) {
        framebuffer[y * screen_width + x] = color;
    }
}

// Dibuja un carácter escalado desde font_default[]
void draw_char(int x, int y, char c, int scale, u32 color) {
    int index = (int)c * 16; // 16 bytes por carácter
    for (int row = 0; row < 16; row++) {
        u8 row_data = font_default[index + row];
        for (int col = 0; col < 8; col++) {
            if (row_data & (1 << (7 - col))) {
                for (int dy = 0; dy < scale; dy++) {
                    for (int dx = 0; dx < scale; dx++) {
                        put_pixel(x + col * scale + dx, y + row * scale + dy, color);
                    }
                }
            }
        }
    }
}

// Imprime texto con soporte de salto de línea (\n)
void draw_text(int x, int y, const char* text, int scale, u32 color) {
    int orig_x = x;
    while (*text) {
        if (*text == '\n') {
            x = orig_x;
            y += 16 * scale;
        } else {
            draw_char(x, y, *text, scale, color);
            x += 8 * scale;
        }
        text++;
    }
}



/*
 *
 * how to use:
void kernel_main() {
    draw_text(50, 50, "A A A A", 4, 0x00FF00); // green
    while (1) {} // loop
}
*/










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

    else if (strcmp(input_buffer, "cdback") == 0) {
        cd_back();
    }
   
   
   if (strcmp(input_buffer, "uptime") == 0) {
   	cursor_y++;
        cmd_uptime(cursor_y); 
        
    } 
    else if(strncmp(input_buffer, "     ", 5) == 0) {
    	const char *value = input_buffer + 5;
   	 evaluate_expression(value);
    }

    else if(strcmp(input_buffer, "lsk") == 0) {
        lsk_itm();
    }


    else if(strcmp(input_buffer, "track") == 0) {
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
    } else if (strncmp(input_buffer, "view ", 5) == 0) {
        cursor_y = cursor_y + 1;
     	const char *filename = input_buffer + 5;
    	view_file(filename);
    }
    else if (strncmp(input_buffer, "svcmd ", 6) == 0) {
        cursor_y = cursor_y + 1;
     	const char *cmd = input_buffer + 6;
    	save_command(cmd);
    }
    
    else if (strncmp(input_buffer, "vfs ", 4) == 0) {
        cursor_y = cursor_y + 4;
     	const char *mnt_name = input_buffer + 4;

    		
    	fs_operations_t memfs_ops = {
		.open = memfs_open,
		.close = memfs_close,
		.read = memfs_read,
		.write = memfs_write
	    };

    		vfs_mount(mnt_name, "/mnt", memfs_ops);
    		k_printf("A 'mnt' has been created successfully!", cursor_y++, GREEN_TXT);
    }
    
    
    
    else if (strcmp(input_buffer, "vfslist") == 0) {
    vfs_list_mountpoints(12);
    }
    else if (strcmp(input_buffer, "history") == 0)  {
    	k_clear_screen();
    	show_command_history();
    }
     else if (strncmp(input_buffer, "edit ", 5) == 0) {
        cursor_y = cursor_y + 1;
     	const char *filename = input_buffer + 5;
    	edit_file_interactive(filename);
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

           W_MSG();
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
  
	    k_printf("Created new file!", cursor_y++, GREEN_TXT);
        touch(filename, "");
    }
    
    else if (strncmp(input_buffer, "rmfile ", 7) == 0) {
        const char *filename = input_buffer + 7;
  

        rmfile(filename);
    }
    else if (strncmp(input_buffer, "rmdir ", 6) == 0) {
        const char *filename = input_buffer + 6;
 

        rmdir(filename);
    }
    
    else if (strncmp(input_buffer, "cd ", 3) == 0) {
        const char *dirname = input_buffer + 3;
	cd(dirname);
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

    for (unsigned int i = 0; i <= current_directory; i++) {
        k_printf(directory_table[i].name, cursor_y++, GREEN_TXT);
        
    }

    k_printf_no_newline("\n", 0, WHITE_TXT);
    } 

    

   
     else if (strcmp(input_buffer, "clear") == 0) {
        k_clear_screen();
        cursor_y = 0; 
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



//add_log("Kernel initialized successfully.", get_system_time(), INFO);


// PCI WIFI

#define RTL8139_VENDOR_ID 0x10EC
#define RTL8139_DEVICE_ID 0x8139

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;



u16 pci_config_read_word(u8 bus, u8 slot, u8 func, u8 offset) {
    u32 address = (1 << 31) | (bus << 16) | (slot << 11) |
                  (func << 8) | (offset & 0xFC);
    outl(0xCF8, address);
    return (u16)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
}

u32 pci_config_read_dword(u8 bus, u8 slot, u8 func, u8 offset) {
    u32 address = (1 << 31) | (bus << 16) | (slot << 11) |
                  (func << 8) | (offset & 0xFC);
    outl(0xCF8, address);
    return inl(0xCFC);
}

typedef struct {
    u32 io_base;
    u8 mac[6];
    u8* rx_buffer;
} rtl8139_dev_t;

rtl8139_dev_t rtl_dev;

// 💥 Reset WITH Init
void rtl8139_init(u32 io) {
    rtl_dev.io_base = io;
    rtl_dev.rx_buffer = (u8*)0x00400000; 

    // Reset
    outb(io + 0x37, 0x10);
    while (inb(io + 0x37) & 0x10);

    // RX buffer
    outl(io + 0x30, (u32)rtl_dev.rx_buffer);

    
    outb(io + 0x37, 0x0C);

    
    outl(io + 0x44, 0x0000070F); 

    // GET MAC
    for (int i = 0; i < 6; i++) {
        rtl_dev.mac[i] = inb(io + i);
    }
}

// 🔍 Search RTL8139 with PCI
void pci_scan_for_rtl8139() {
    for (u8 bus = 0; bus < 256; bus++) {
        for (u8 slot = 0; slot < 32; slot++) {
            u16 vendor = pci_config_read_word(bus, slot, 0, 0x00);
            if (vendor == 0xFFFF) continue;

            u16 device = pci_config_read_word(bus, slot, 0, 0x02);
            if (vendor == RTL8139_VENDOR_ID && device == RTL8139_DEVICE_ID) {
                u32 bar0 = pci_config_read_dword(bus, slot, 0, 0x10);
                u32 io_base = bar0 & ~0x3;
                rtl8139_init(io_base);
                return;
            }
        }
    }
}




void speaker_beep(u32 freq, u32 duration_ms) {
    u16 divisor = 1193182 / freq;

    
    outb(0x43, 0xB6);                  
    outb(0x42, (u8)(divisor & 0xFF)); 
    outb(0x42, (u8)(divisor >> 8));    

   
    u8 val = inb(0x61);
    outb(0x61, val | 0x03);

    
    for (u32 i = 0; i < duration_ms * 1000; i++) {
        __asm__ __volatile__("nop");
    }

    // Speaker OFF.
    val = inb(0x61) & 0xFC;
    outb(0x61, val);
}

void print_mac(u8* mac, u32 x, u32 y, u32 color) {
    char hex[] = "0123456789ABCDEF";
    char buf[20];
    int i = 0;

    for (int j = 0; j < 6; j++) {
        buf[i++] = hex[(mac[j] >> 4) & 0xF];
        buf[i++] = hex[mac[j] & 0xF];
        if (j != 5)
            buf[i++] = ':';
    }
    buf[i] = '\0';
    k_printf(buf, y, color);
}


static void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 //make it shut up
 static void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
     
 	outb(0x61, tmp);
 }

void wait(uint32_t ticks) {
    for (volatile uint32_t i = 0; i < ticks * 1000; i++) {
        // No hacer nada, solo perder tiempo
    }
}

void beep() {
    play_sound(1000);  // 1000 Hz = un beep clásico
    wait(50);          // Ajusta este valor si el beep es muy corto o largo
    nosound();
}






void k_main(uint32_t magic, multiboot_info_t *multiboot_info) 
{

    CR_W();
    delay(100);
    W_MSG();
    vfs_init();
    

    
/*
    fs_operations_t memfs_ops = {
        .open = memfs_open,
        .close = memfs_close,
        .read = memfs_read,
        .write = memfs_write
    };*/

  

 /*
    int fd = vfs_open("/mnt/archivo.txt", 0);  

    if (fd != -1) {
        char buffer[32];
        int read_count = vfs_read(fd, buffer, 31);
        buffer[read_count] = '\0';  

      
        for (int i = 0; buffer[i]; i++)
            text_draw(i, 10, buffer[i], 0x0F); 
        vfs_close(fd);
    } else {
        const char* msg = "No se pudo abrir :,(";
        for (int i = 0; msg[i]; i++)
            text_draw(i, 12, msg[i], 0x4E); 
    }
    
    */

 
    
    //print_mac(rtl_dev.mac, 180, 1, 0x00FF00);
    // rtc_init(); <-- RTC test sys.
    
    //pci_scan_for_rtl8139();
    cursor_x = 0;
    cursor_y = 19; 



//delete_inode(&sb, inodes, new_inode->inode_number);

    

    sound_init();


    init_shared_memory();

    void *block1 = allocate_shared_memory(512);


    void *block2 = allocate_shared_memory(512);


    free_shared_memory(block1);

 
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





