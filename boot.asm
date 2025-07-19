BITS 16
ORG 0x7C00

start:
    mov si, msg
    call print_string

    cli
    hlt

print_string:
    mov ah, 0x0E
.loop:
    lodsb
    or al, al
    jz .done
    int 0x10
    jmp .loop
.done:
    ret

msg db "FAT12 Bootloader OK!", 0

times 510-($-$$) db 0
dw 0xAA55  ; Firma de arranque

