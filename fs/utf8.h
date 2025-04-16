/*
*
*   utf8-core.h - a generic file for utf core
*
*  (C) 2025 Angel Nieto/NopAngel <angelnieto1402@gmail.com>
*
*           This code is licenced under the APACHE 2.0
*/


#ifndef UTF8_H
#define UTF8_H

// Definición de tipos básicos
typedef unsigned int size_t; // Tamaño como tipo entero sin signo
typedef unsigned char uint8_t; // Byte único para operaciones

// Estructura para mapear Unicode
struct unicode_map {
    unsigned int version; // Versión de UTF-8 (ejemplo: 1 para Unicode 1.0)
};

// Estructura para manejar cadenas UTF-8
struct qstr {
    const char *name; // Puntero a los datos de la cadena
    size_t len;       // Longitud de la cadena
};

// Funciones para trabajar con UTF-8
int utf8_validate(const struct unicode_map *um, const struct qstr *str);
int utf8_strncmp(const struct unicode_map *um, const struct qstr *s1, const struct qstr *s2);
int utf8_normalize(const struct unicode_map *um, const struct qstr *str, char *dest, size_t dlen);
int utf8_decode(const char *str, size_t *index, size_t len);

#endif // UTF8_H
