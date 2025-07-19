// types.hpp - Tipos de datos básicos para BearOS
// Compatible con entornos bare metal sin stdlib

#pragma once

// Tipos enteros sin signo
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

// Tipos enteros con signo
typedef char      int8_t;
typedef short     int16_t;
typedef int       int32_t;
typedef long long int64_t;

// Tamaños y punteros
typedef uint32_t  size_t;
typedef int32_t   ssize_t;
typedef uint32_t  uintptr_t;

// Booleanos básicos (si no usás C99)
#define TRUE  1
#define FALSE 0

// Nulo
#define NULL 0

// Evita colisiones si usás C
#ifdef __cplusplus
extern "C" {
#endif

// (Podés agregar funciones utilitarias acá si querés)

#ifdef __cplusplus
}
#endif

