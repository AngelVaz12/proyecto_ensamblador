; funciones.asm
section .text
global mostrarLaberinto
global puedeMover
extern printf

mostrarLaberinto:
    ; void mostrarLaberinto(char* lab, int filas, int columnas)
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]  ; lab pointer
    mov ecx, [ebp+12] ; filas
    mov edx, [ebp+16] ; columnas

    push edi
    mov edi, eax      ; edi = lab pointer

.outer_loop:
    push ecx
    mov ecx, edx      ; columnas
.inner_loop:
    mov al, [edi]
    push eax
    push format
    call printf
    add esp, 8
    inc edi
    loop .inner_loop

    push newline
    call printf
    add esp, 4

    pop ecx
    loop .outer_loop

    pop edi
    pop ebp
    ret

section .data
    format db "%c", 0
    newline db 10, 0
