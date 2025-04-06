section .data
    vga_mode db 0x13           ; Modo gráfico 320x200 con 256 colores
    vga_port_crtc dw 0x3D4     ; Puerto para el registro de control del CRT

section .bss
    framebuffer resb 64000     ; Buffer de memoria para píxeles (320x200)

section .text
    global _start

_start:
    ; Establecer modo gráfico VGA
    call set_vga_mode

    ; Limpiar la pantalla
    call clear_screen

    ; Dibujar un cuadrado en la pantalla
    mov ax, 50     ; Posición X
    mov bx, 50     ; Posición Y
    mov cx, 20     ; Tamaño del cuadrado
    mov dx, 15     ; Color
    call draw_square

    hlt             ; Detener ejecución

; -------------------------------
; Establecer modo gráfico VGA
; -------------------------------
set_vga_mode:
    mov ax, 0x00
    int 0x10        ; Llamada a la BIOS para video
    ret

; -------------------------------
; Limpiar la pantalla
; -------------------------------
clear_screen:
    mov ax, 0xA000  ; Dirección base de memoria de video
    mov es, ax      ; Establecer segmento
    xor di, di      ; Empezar en el inicio
    mov cx, 64000   ; Limpiar toda la memoria (320x200)
    mov al, 0x00    ; Color negro
    rep stosb       ; Llenar con color
    ret

; -------------------------------
; Dibujar un píxel en la pantalla
; -------------------------------
draw_pixel:
    mov ax, 0xA000  ; Dirección base de memoria de video
    mov es, ax      ; Establecer segmento
    mov di, bx      ; Calcular la posición (X)
    add di, ax      ; Calcular la posición (Y)
    mov al, dl      ; Establecer color
    stosb           ; Escribir en memoria
    ret

; -------------------------------
; Dibujar un cuadrado en la pantalla
; -------------------------------
draw_square:
    push cx          ; Guardar tamaño
draw_square_loop:
    push cx          ; Guardar tamaño de lado
    mov dx, bx       ; Establecer Y
draw_square_side:
    call draw_pixel  ; Dibujar píxel
    inc dx           ; Incrementar Y
    loop draw_square_side
    pop cx           ; Restaurar tamaño de lado
    inc ax           ; Incrementar X
    loop draw_square_loop
    pop cx           ; Restaurar tamaño
    ret
