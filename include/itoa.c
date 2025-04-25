/*
*
*   itoa.c - my own itoa (important file)
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/


void itoa(int value, char *str, int base) {
    // Punteros para construir la cadena
    char *ptr = str, *ptr1 = str, tmp_char;
    int tmp_value;

    // Manejar números negativos (solo para base 10)
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }

    // Construcción de la cadena
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789ABCDEF"[tmp_value - value * base];
    } while (value);

    // Finalizar la cadena con '\0'
    *ptr-- = '\0';

    // Invertir la cadena para obtener el número correctamente
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }

    // Nueva funcionalidad: manejar bases no válidas
    if (base < 2 || base > 16) {
        str[0] = '\0'; // Retorna cadena vacía si la base no es válida
    }
}
