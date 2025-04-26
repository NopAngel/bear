section .data
    vga_mode db 0x13                
    vga_palette_port db 0x03C8      ; 
    vga_data_port db 0x03C9         ; 
    framebuffer resb 64000          ;

section .text
    global _start

_start:

    call set_vga_mode

  
    mov al, 0x02          ; color bg
    call clear_screen

  
    mov ax, 50            ; x initial
    mov bx, 50            ; y initial
    mov cx, 100           ; width
    mov dx, 50            ; height
    mov si, 0x1C          ; 
    call draw_filled_rect

 
    mov ax, 10            ; x initial
    mov bx, 150           ; y initial
    mov cx, 200          
    mov dx, 0x4F          ; color
    call draw_horizontal_line

    mov ax, 100          
    mov bx, 20           
    mov cx, 150         
    mov dx, 0x3F          
    call draw_vertical_line

    call set_palette

    
    jmp $


set_vga_mode:
    mov ah, 0x00
    mov al, [vga_mode]
    int 0x10
    ret


clear_screen:
    mov ax, 0xA000        
    mov es, ax
    xor di, di           
    mov cx, 64000         
    rep stosb
    ret

draw_pixel:
    push ax               
    push bx
    mov ax, 0xA000        
    mov es, ax
    mov di, bx           
    mul cx            
    add di, ax            
    mov al, dl            
    stosb
    pop bx             
    pop ax
    ret


draw_horizontal_line:
    mov si, ax         
draw_h_line_loop:
    call draw_pixel     
    inc si
    loop draw_h_line_loop
    ret

draw_vertical_line:
    mov si, bx            
draw_v_line_loop:
    call draw_pixel       
    inc si
    loop draw_v_line_loop
    ret

draw_filled_rect:
    push cx               
rect_fill_loop:
    call draw_horizontal_line
    inc bx
    loop rect_fill_loop
    pop cx               
    ret

set_palette:
    mov dx, [vga_palette_port]
    xor al, al
    out dx, al            
    mov dx, [vga_data_port]
    mov cx, 256           ; 256 colors!!!
set_palette_loop:
    mov al, cl            ; intensity for the red
    out dx, al
    mov al, ch            ; intensity for the green
    out dx, al
    out dx, al            ; intensity for the blue 
    loop set_palette_loop
    ret

scroll_screen:
    mov ax, 0xA000        ; direction base for vga
    mov es, ax
    lea si, [es:0x01400]  
    xor di, di            
    mov cx, 63200        
    rep movsb             
    ret
