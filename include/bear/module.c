#include "./module.h"


static Module* module_list = (void*)0;


void register_module(Module* module) {
    if (!module) return;

    module->next = module_list;
    module_list = module;


    if (module->init) {
        module->init();
    }

    k_printf("Módulo registrado: %s (v%d)\n", 30, 0x0A); 
}

void unregister_module(const char* name) {
    if (!module_list) return;

    Module* current = module_list;
    Module* previous = (void*)0;

    while (current) {
        if (current->name && name && strcmp(current->name, name) == 0) {
            if (current->exit) {
                current->exit();
            }

    
            if (previous) {
                previous->next = current->next;
            } else {
                module_list = current->next;
            }

            k_printf("Módulo eliminado: %s\n", 31, 0x0C);
            return;
        }

        previous = current;
        current = current->next;
    }
}

uint8_t load_module(const char* name) {
    k_printf("Cargando módulo: %s\n", 32, 0x07);
    return 1;
}

uint8_t unload_module(const char* name) {
    k_printf("Descargando módulo: %s\n", 33, 0x07);
    unregister_module(name);
    return 1;
}


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