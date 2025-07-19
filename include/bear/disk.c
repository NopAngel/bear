
#define MAX_DIRECTORIES 128 // Máximo número de directorios
#define MAX_NAME_LENGTH 12  // Longitud máxima del nombre de la carpeta
#define DISK_SIZE 1024 * 1024 // Tamaño del "disco" virtual (1 MB)
#define MAX_FILES 128 // Máximo número de archivos
#define MAX_FILENAME_LENGTH 12 // Longitud máxima del nombre del archivo



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
