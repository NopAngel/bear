#include "utf8.h"  // Archivo de cabecera personalizado

struct unicode_map {
    unsigned int version;
    // Otras configuraciones del mapa de caracteres UTF-8
};

struct qstr {
    const char *name;
    size_t len;
};

// Validar una cadena UTF-8
int utf8_validate(const struct unicode_map *um, const struct qstr *str) {
    size_t index = 0;
    while (index < str->len) {
        int code_point = utf8_decode(str->name, &index, str->len);
        if (code_point == -1) {
            return -1;  // Cadena inválida
        }
    }
    return 0;  // Cadena válida
}

// Comparar dos cadenas en UTF-8
int utf8_strncmp(const struct unicode_map *um, const struct qstr *s1, const struct qstr *s2) {
    size_t index1 = 0, index2 = 0;

    while (index1 < s1->len && index2 < s2->len) {
        int code1 = utf8_decode(s1->name, &index1, s1->len);
        int code2 = utf8_decode(s2->name, &index2, s2->len);

        if (code1 == -1 || code2 == -1) {
            return -1;  // Error en la decodificación
        }
        if (code1 != code2) {
            return 1;  // Las cadenas son diferentes
        }
    }

    if (index1 == s1->len && index2 == s2->len) {
        return 0;  // Las cadenas son iguales
    }
    return 1;  // Una cadena es más corta que la otra
}

// Normalizar cadenas UTF-8
int utf8_normalize(const struct unicode_map *um, const struct qstr *str, char *dest, size_t dlen) {
    size_t index = 0, dest_index = 0;

    while (index < str->len && dest_index < dlen) {
        int code_point = utf8_decode(str->name, &index, str->len);
        if (code_point == -1) {
            return -1;  // Error en la decodificación
        }
        dest[dest_index++] = (char)code_point;  // Copiar el carácter normalizado
    }
    if (dest_index < dlen) {
        dest[dest_index] = '\0';  // Terminar la cadena
        return 0;
    }
    return -1;  // Espacio insuficiente en el destino
}

// Decodificar un carácter UTF-8
int utf8_decode(const char *str, size_t *index, size_t len) {
    unsigned char first_byte = str[*index];
    int code_point;
    size_t remaining_bytes;

    if ((first_byte & 0x80) == 0) {
        code_point = first_byte;
        remaining_bytes = 0;
    } else if ((first_byte & 0xE0) == 0xC0) {
        code_point = first_byte & 0x1F;
        remaining_bytes = 1;
    } else if ((first_byte & 0xF0) == 0xE0) {
        code_point = first_byte & 0x0F;
        remaining_bytes = 2;
    } else if ((first_byte & 0xF8) == 0xF0) {
        code_point = first_byte & 0x07;
        remaining_bytes = 3;
    } else {
        return -1;  // Byte inicial inválido
    }

    for (size_t i = 0; i < remaining_bytes; i++) {
        (*index)++;
        if (*index >= len || (str[*index] & 0xC0) != 0x80) {
            return -1;  // Byte de continuación inválido
        }
        code_point = (code_point << 6) | (str[*index] & 0x3F);
    }

    (*index)++;
    return code_point;
}
