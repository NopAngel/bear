#include "rtc_driver.h"
#include "bear/k_printf.h" // Para usar k_printf

int main() {
    uint8_t hours, minutes, seconds;
    uint8_t day, month, year;

    // Inicializa el controlador RTC
    rtc_init();

    // Obtén la hora actual
    rtc_get_time(&hours, &minutes, &seconds);
    k_printf("Hora actual: %02d:%02d:%02d\n", 10, 0x0F); // Línea 10, color blanco brillante

    // Obtén la fecha actual
    rtc_get_date(&day, &month, &year);
    k_printf("Fecha actual: %02d/%02d/%02d\n", 11, 0x0F); // Línea 11

    return 0;
}
