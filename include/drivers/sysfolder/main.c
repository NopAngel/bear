#include "fs_driver.h"

int main() {
    // Inicializa el sistema de archivos
    fs_init();

    // Crea archivos de ejemplo
    fs_create_file("archivo1.txt", 1024);
    fs_create_file("archivo2.txt", 2048);

    // Lista los archivos
    fs_list_files();

    // Lee datos de un archivo
    uint8_t buffer[512];
    fs_read_file("archivo1.txt", buffer, 512, 0);

    // Escribe datos en un archivo
    uint8_t data[512] = {0x01, 0x02, 0x03};
    fs_write_file("archivo1.txt", data, 3, 0);

    return 0;
}
