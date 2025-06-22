section .text
global _mostrarLaberinto
global _puedeMover
extern _printf

_mostrarLaberinto:
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]   ; lab
    mov ecx, [ebp+12]  ; filas
    mov edx, [ebp+16]  ; columnas

    push edi
    mov edi, eax

.filas_loop:
    push ecx
    mov ecx, edx

.columnas_loop:
    mov al, [edi]
    movzx eax, al
    push eax
    push format
    call _printf
    add esp, 8
    inc edi
    loop .columnas_loop

    push newline
    call _printf
    add esp, 4

    pop ecx
    loop .filas_loop

    pop edi
    pop ebp
    ret

_puedeMover:
    push ebp
    mov ebp, esp

    mov eax, [ebp+8]    ; lab
    mov ecx, [ebp+12]   ; filas
    mov edx, [ebp+16]   ; columnas
    mov esi, [ebp+20]   ; x
    mov edi, [ebp+24]   ; y

    cmp esi, 0
    jl .no
    cmp esi, ecx
    jge .no
    cmp edi, 0
    jl .no
    cmp edi, edx
    jge .no

    imul esi, edx
    add esi, edi
    add eax, esi
    mov bl, [eax]
    cmp bl, '#'
    je .no

    mov eax, 1
    jmp .end

.no:
    mov eax, 0

.end:
    pop ebp
    ret

section .data
format db "%c", 0
newline db 10, 0
