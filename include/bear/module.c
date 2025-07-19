#include "module.h"
#include "bear/printk.h" // Usamos k_printf para mostrar mensajes

// Lista enlazada de módulos cargados
static Module* module_list = (void*)0;

// Registra un módulo en el sistema
void register_module(Module* module) {
    if (!module) return;

    module->next = module_list; // Añade el módulo al inicio de la lista
    module_list = module;

    // Llama a la función de inicialización del módulo
    if (module->init) {
        module->init();
    }

    k_printf("Módulo registrado: %s (v%d)\n", 30, 0x0A); // Línea 30, color verde
}

// Desregistra un módulo del sistema
void unregister_module(const char* name) {
    if (!module_list) return;

    Module* current = module_list;
    Module* previous = (void*)0;

    while (current) {
        if (current->name && name && strcmp(current->name, name) == 0) {
            // Llama a la función exit del módulo
            if (current->exit) {
                current->exit();
            }

            // Elimina el módulo de la lista
            if (previous) {
                previous->next = current->next;
            } else {
                module_list = current->next;
            }

            k_printf("Módulo eliminado: %s\n", 31, 0x0C); // Línea 31, color rojo
            return;
        }

        previous = current;
        current = current->next;
    }
}

// Carga un módulo dinámicamente (simulado)
uint8_t load_module(const char* name) {
    k_printf("Cargando módulo: %s\n", 32, 0x07); // Línea 32, color blanco
    // Aquí podrías implementar lógica específica para cargar un módulo dinámico
    return 1;
}

// Descarga un módulo dinámicamente
uint8_t unload_module(const char* name) {
    k_printf("Descargando módulo: %s\n", 33, 0x07); // Línea 33, color blanco
    unregister_module(name);
    return 1;
}

// Lista todos los módulos cargados
void list_modules() {
    Module* current = module_list;
    uint32_t index = 0;

    k_printf("Módulos cargados:\n", 34, 0x07); // Línea 34
    while (current) {
        k_printf("%d. %s (v%d)\n", 35 + index, 0x07); // Línea incremental
        current = current->next;
        index++;
    }
}

/*

HOW TO USE??


 EXAMPLE: 
#include "module.h"
#include "bear/printk.h"

// Funciones del módulo
void example_init() {
    k_printf("Módulo de ejemplo inicializado.\n", 36, 0x0A);
}

void example_exit() {
    k_printf("Módulo de ejemplo desconectado.\n", 37, 0x0C);
}

// Definición del módulo
Module example_module = {
    .name = "Example Module",
    .version = 1,
    .init = example_init,
    .exit = example_exit,
    .next = (void*)0
};


*/