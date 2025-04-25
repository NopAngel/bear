section .data
cpu_status dw 0, 0, 0, 0
cpu_interrupt_flags dw 0, 0, 0, 0

section .text
global cpu_init, cpu_start, cpu_stop, cpu_status_check, cpu_enable_interrupts, cpu_disable_interrupts

cpu_init:
    xor eax, eax
    mov ecx, 4
.init_loop:
    mov [cpu_status + eax * 2], 0
    mov [cpu_interrupt_flags + eax * 2], 0
    inc eax
    loop .init_loop
    ret

cpu_start:
    mov eax, [esp + 4]
    cmp eax, 4
    jae .error
    mov [cpu_status + eax * 2], 1
    ret
.error:
    ret

cpu_stop:
    mov eax, [esp + 4]
    cmp eax, 4
    jae .error
    mov [cpu_status + eax * 2], 0
    ret

cpu_status_check:
    mov eax, [esp + 4]
    cmp eax, 4
    jae .error_status
    mov ax, [cpu_status + eax * 2]
    ret
.error_status:
    mov eax, 0xFFFFFFFF
    ret

cpu_enable_interrupts:
    mov eax, [esp + 4]
    cmp eax, 4
    jae .error_interrupts
    mov [cpu_interrupt_flags + eax * 2], 1
    ; Instrucción típica para habilitar interrupciones en x86
    sti
    ret
.error_interrupts:
    ret

cpu_disable_interrupts:
    mov eax, [esp + 4]
    cmp eax, 4
    jae .error_interrupts
    mov [cpu_interrupt_flags + eax * 2], 0
    ; Instrucción típica para deshabilitar interrupciones en x86
    cli
    ret
