section .data
vertex_position dd 0.0, 0.0, 0.0
vertex_color dd 1.0, 1.0, 1.0
model_matrix dd 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0
view_matrix dd 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0
projection_matrix dd 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0
output_color dd 0.0, 0.0, 0.0, 0.0

section .text
global shader_main

shader_main:
    push ebp
    mov ebp, esp
    mov eax, vertex_position
    mov ebx, model_matrix
    call matrix_multiply
    mov vertex_position, eax
    mov ebx, view_matrix
    call matrix_multiply
    mov vertex_position, eax
    mov ebx, projection_matrix
    call matrix_multiply
    mov vertex_position, eax
    mov eax, vertex_color
    mov output_color, eax
    pop ebp
    ret

matrix_multiply:
    ret
