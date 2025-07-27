#ifndef _XEN_DRIVER_H
#define _XEN_DRIVER_H

// Hypercall ABI (based in Xen 4.x)
#define __HYPERVISOR_set_trap_table        0
#define __HYPERVISOR_mmu_update            1
#define __HYPERVISOR_console_io            18

struct xen_hypercall_regs {
    unsigned long rax, rdi, rsi, rdx, r10, r8, r9;
};

// inited
int xen_init();

// Hypercall  generic
unsigned long xen_hypercall(unsigned int op, void *arg);

//  writting
void xen_console_write(const char *str, unsigned int len);

#endif // _XEN_DRIVER_H