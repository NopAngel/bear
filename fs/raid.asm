section .data
    command_read db 0x20    
    command_write db 0x30   
    drive_port dw 0x1F0     

section .bss
    buffer resb 512         

section .text
    global _start
_start:
 
    call wait_ready


    mov dx, [drive_port]   
    mov al, [command_read]  
    out dx, al     

 
    mov cx, 256             
    lea di, [buffer]        
read_sector:
    in ax, dx             
    stosw                   
    loop read_sector        

    hlt                   

wait_ready:
    mov dx, [drive_port + 7] 
.wait:
    in al, dx
    test al, 0x80          
    jnz .wait
    ret
