
#define IDT_SIZE 256
#define KERNEL_CS 0x08 // Selector de segmento de código del kernel

// Estructura para una entrada en la IDT (Interrupt Descriptor Table)
struct idt_entry {
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

// Declaración de una función ASM para cargar la IDT
extern void load_idt(unsigned int);

// Función para configurar una entrada en la IDT
void set_idt_gate(int n, unsigned int handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].base_high = (handler >> 16) & 0xFFFF;
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; // Interrupción presente y privilegio del kernel
}

// Inicializar la IDT
void init_idt() {
    idt_reg.base = (unsigned int)&idt;
    idt_reg.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;

    // Configurar una interrupción para manejar excepciones
    set_idt_gate(0, (unsigned int)isr0_handler);

    // Cargar la IDT
    load_idt((unsigned int)&idt_reg);
    // k_printf("IDT inicializada.\n", 0, 0x0F);
}

// Ejemplo de manejador de interrupción
void isr0_handler() {
    // k_printf("Interrupción 0 recibida.\n", 1, 0x04);
    while (1); // Detiene la ejecución en caso de excepción crítica
}
