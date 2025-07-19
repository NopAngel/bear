void shutdown_system() {
    asm volatile (
        "movl $0x5307, %eax \n"
        "movl $0x0001, %ebx \n"
        "movl $0x0003, %ecx \n"
        "int $0x15"
    );
}

