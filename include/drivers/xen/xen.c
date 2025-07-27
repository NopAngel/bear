#include "xen.h"
#include "../../../fs/k_printf.h"

#define GREEN_TXT 0x02
#define RED_TXT 0x04
#define YELLOW_TXT 0x0E

static void *hypercall_page = (void *)0x100000; 

// Hypercall ASM (x86-64)
static inline unsigned long xen_hypercall_asm(
    unsigned int op, 
    void *arg
) {
    unsigned long result;
    asm volatile (
        "call *%[hypercall_page]"
        : "=a" (result)
        : [hypercall_page] "r" (hypercall_page),
          "a" (op), 
          "D" (arg)
        : "memory"
    );
    return result;
}

int xen_init() {

    const char *xen_signature = (const char *)0x100000;
    if (xen_signature[0] != 'X' || xen_signature[1] != 'e' || xen_signature[2] != 'n') {
        k_printf("Xen: Not found hypervisor!", 19, RED_TXT);
        return -1;
    }

    k_printf("Xen: hypervisor detected!", 0, GREEN_TXT);
    return 0;
}


unsigned long xen_hypercall(unsigned int op, void *arg) {
    return xen_hypercall_asm(op, arg);
}


void xen_console_write(const char *str, unsigned int len) {
    struct xen_hypercall_regs regs = {
        .rax = __HYPERVISOR_console_io,
        .rdi = 1, 
        .rsi = (unsigned long)str,
        .rdx = len
    };
    xen_hypercall_asm(__HYPERVISOR_console_io, &regs);
}


/*



void k_main(uint32_t magic, multiboot_info_t *multiboot_info) {


    // inited
    if (xen_init() == 0) {
        k_printf("Xen: Driver loaded!", 0, GREEN_TXT);

        // example: writting in the console (xen console)
        xen_console_write("BearOS in XEN!\n", 26);
    }

    while (1) { }
}

*/