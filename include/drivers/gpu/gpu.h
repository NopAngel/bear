
// Estructura para una entrada en la IDT (Interrupt Descriptor Table)
/*struct idt_entry {
    unsigned short base_low;  // Bits bajos de la dirección del handler
    unsigned short sel;       // Segmento de código del handler
    unsigned char always0;    // Siempre 0
    unsigned char flags;      // Flags de tipo/privilegios
    unsigned short base_high; // Bits altos de la dirección del handler
} __attribute__((packed));    // Evitar padding

// Estructura para el registro de la IDT
struct idt_ptr {
    unsigned short limit;    // Tamaño de la IDT
    unsigned int base;       // Dirección base de la IDT
} __attribute__((packed));

struct idt_entry idt[IDT_SIZE];
struct idt_ptr idt_reg;





*/


#ifndef GPU_H
#define GPU_H
void isr0_handler() ;
void init_idt();
void set_idt_gate(int n, unsigned int handler):
#endif
