#include "rtc_driver.h"

// Función para leer un registro del RTC
static uint8_t rtc_read_register(uint8_t reg) {
    // Escribe en el puerto de dirección del RTC
    asm volatile("outb %0, %1" : : "a"(reg), "Nd"(RTC_ADDRESS_PORT));
    // Lee del puerto de datos del RTC
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(RTC_DATA_PORT));
    return value;
}

// Inicializa el RTC
void rtc_init() {
    // Aquí podrías habilitar interrupciones del RTC si lo necesitas
    // Para este ejemplo básico, simplemente configuramos acceso al RTC
}

// Obtiene la hora actual
void rtc_get_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds) {
    // Lee los registros de hora, minuto y segundo
    *hours = rtc_read_register(0x04);   // Registro de horas
    *minutes = rtc_read_register(0x02); // Registro de minutos
    *seconds = rtc_read_register(0x00); // Registro de segundos
}

// Obtiene la fecha actual
void rtc_get_date(uint8_t* day, uint8_t* month, uint8_t* year) {
    // Lee los registros de día, mes y año
    *day = rtc_read_register(0x07);  // Registro de día
    *month = rtc_read_register(0x08); // Registro de mes
    *year = rtc_read_register(0x09);  // Registro de año
}
