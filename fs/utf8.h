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


typedef unsigned int size_t;
typedef unsigned char uint8_t; 


struct unicode_map {
    unsigned int version;
};


struct qstr {
    const char *name; 
    size_t len;       
};


int utf8_validate(const struct unicode_map *um, const struct qstr *str);
int utf8_strncmp(const struct unicode_map *um, const struct qstr *s1, const struct qstr *s2);
int utf8_normalize(const struct unicode_map *um, const struct qstr *str, char *dest, size_t dlen);
int utf8_decode(const char *str, size_t *index, size_t len);

#endif // UTF8_H
