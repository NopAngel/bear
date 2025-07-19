/*
 * BearOS - Module Header
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef BEAROS_MODULE_H
#define BEAROS_MODULE_H

// Tipos básicos
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Estructura básica de un módulo
typedef struct Module {
    const char* name;             // Nombre del módulo
    uint32_t version;             // Versión del módulo
    void (*init)(void);           // Función de inicialización del módulo
    void (*exit)(void);           // Función para limpiar/desconectar el módulo
    struct Module* next;          // Siguiente módulo (en caso de lista enlazada)
} Module;

// Registro y manejo de módulos
void register_module(Module* module);
void unregister_module(const char* name);

// Carga dinámica de un módulo (simulado)
uint8_t load_module(const char* name);

// Descarga un módulo
uint8_t unload_module(const char* name);

// Listar módulos cargados (para diagnóstico)
void list_modules();

#endif // BEAROS_MODULE_H
