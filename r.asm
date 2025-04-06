section .data
    vga_mode db 0x13                ; Modo gráfico 320x200 con 256 colores
    vga_palette_port db 0x03C8      ; Puerto para la paleta de colores
    vga_data_port db 0x03C9         ; Puerto para datos de la paleta
    framebuffer resb 64000          ; Buffer de 320x200 píxeles (64000 bytes)

section .text
    global _start

_start:
    ; Establecer el modo VGA
    call set_vga_mode

    ; Limpiar la pantalla con un color de fondo
    mov al, 0x02          ; Color de fondo
    call clear_screen

    ; Dibujar un rectángulo relleno
    mov ax, 50            ; X inicial
    mov bx, 50            ; Y inicial
    mov cx, 100           ; Ancho
    mov dx, 50            ; Alto
    mov si, 0x1C          ; Color del rectángulo
    call draw_filled_rect

    ; Dibujar una línea horizontal
    mov ax, 10            ; X inicial
    mov bx, 150           ; Y inicial
    mov cx, 200           ; Longitud
    mov dx, 0x4F          ; Color
    call draw_horizontal_line

    ; Dibujar una línea vertical
    mov ax, 100           ; X inicial
    mov bx, 20            ; Y inicial
    mov cx, 150           ; Longitud
    mov dx, 0x3F          ; Color
    call draw_vertical_line

    ; Configurar la paleta de colores
    call set_palette

    ; Ciclo infinito
    jmp $

; -------------------------------
; Funciones del controlador VGA
; -------------------------------

; Cambia el modo VGA a 320x200, 256 colores
set_vga_mode:
    mov ah, 0x00
    mov al, [vga_mode]
    int 0x10
    ret

; Limpia la pantalla con un color específico
clear_screen:
    mov ax, 0xA000        ; Dirección base de memoria VGA
    mov es, ax
    xor di, di            ; Inicio de la memoria
    mov cx, 64000         ; 320x200 píxeles
    rep stosb
    ret

; Dibujar un píxel en la pantalla
draw_pixel:
    push ax               ; Guardar registros
    push bx
    mov ax, 0xA000        ; Dirección base de memoria VGA
    mov es, ax
    mov di, bx            ; Calcular posición en Y
    mul cx                ; Multiplicar por ancho de la pantalla
    add di, ax            ; Sumar posición en X
    mov al, dl            ; Color del píxel
    stosb
    pop bx                ; Restaurar registros
    pop ax
    ret

; Dibujar una línea horizontal
draw_horizontal_line:
    mov si, ax            ; Guardar X inicial
draw_h_line_loop:
    call draw_pixel       ; Dibujar píxel
    inc si
    loop draw_h_line_loop
    ret

; Dibujar una línea vertical
draw_vertical_line:
    mov si, bx            ; Guardar Y inicial
draw_v_line_loop:
    call draw_pixel       ; Dibujar píxel
    inc si
    loop draw_v_line_loop
    ret

; Dibujar un rectángulo relleno
draw_filled_rect:
    push cx               ; Guardar ancho
rect_fill_loop:
    call draw_horizontal_line
    inc bx                ; Siguiente fila
    loop rect_fill_loop
    pop cx                ; Restaurar ancho
    ret

; Configurar una paleta de colores personalizada
set_palette:
    mov dx, [vga_palette_port]
    xor al, al
    out dx, al            ; Iniciar escritura en la paleta
    mov dx, [vga_data_port]
    mov cx, 256           ; 256 colores
set_palette_loop:
    mov al, cl            ; Intensidad de rojo
    out dx, al
    mov al, ch            ; Intensidad de verde
    out dx, al
    out dx, al            ; Intensidad de azul (igual a verde)
    loop set_palette_loop
    ret

; Desplazar la pantalla hacia abajo
scroll_screen:
    mov ax, 0xA000        ; Dirección base de memoria VGA
    mov es, ax
    lea si, [es:0x01400]  ; Dirección de la segunda fila (320 bytes)
    xor di, di            ; Comienzo de la memoria
    mov cx, 63200         ; Copiar 316 filas (316*200 bytes)
    rep movsb             ; Desplazar filas hacia arriba
    ret
