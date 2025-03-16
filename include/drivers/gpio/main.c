#include "gpio_driver.h"
#include "bear/k_printf.h" // Para usar k_printf

int main() {
    // Inicializa el controlador GPIO
    gpio_init();

    // Configura el pin 0 como salida y el pin 1 como entrada
    gpio_set_mode(0, GPIO_MODE_OUTPUT);
    gpio_set_mode(1, GPIO_MODE_INPUT);

    // Escribe un valor alto en el pin 0
    gpio_write(0, GPIO_HIGH);

    // Lee el estado del pin 1
    uint8_t value = gpio_read(1);

    // Muestra el estado del pin 1 en pantalla
    k_printf("Pin 1 estado: %d\n", 10, 0x0F); // Línea 10, color blanco brillante

    return 0;
}
