section .text
    global mover_personaje

mover_personaje:
    ; rcx   ; PUNTERO A LA MATRIZ
    ; dx    ; RENGLONES
    ; r8    ; COLUMNAS
    ; r9    ; TECLA PRESIONADA

    push rbx
    push rsi
    push rdi
    push rbp

    mov rsi, rcx      ; rsi = puntero al mapa
    mov rbx, 0        ; índice lineal
    imul rdx, r8      ; rdx = ren * col → total de elementos
    mov rbp, r9       ; tecla ingresada

.buscar_P:
    cmp rbx, rdx
    jge .fin

    mov al, [rsi + rbx]
    cmp al, 'P'
    je .avanzar

    inc rbx
    jmp .buscar_P

.avanzar:
    cmp rbp, 'd'
    je .derecha

    cmp rbp, 'a'
    je .izquierda

    cmp rbp, 'w'
    je .arriba

    cmp rbp, 's'
    je .abajo

    jmp .fin

.derecha:
    inc rbx
    mov al, [rsi + rbx]
    cmp al, '#'
    je .fin

    mov al, 'P'
    mov [rsi + rbx], al

    dec rbx
    mov al, '.'
    mov [rsi + rbx], al
    jmp .fin

.izquierda:
    dec rbx
    mov al, [rsi + rbx]
    cmp al, '#'
    je .fin

    mov al, 'P'
    mov [rsi + rbx], al

    inc rbx
    mov al, '.'
    mov [rsi + rbx], al
    jmp .fin

.arriba:
    sub rbx, r8
    mov al, [rsi + rbx]
    cmp al, '#'
    je .fin

    mov al, 'P'
    mov [rsi + rbx], al

    add rbx, r8
    mov al, '.'
    mov [rsi + rbx], al
    jmp .fin

.abajo:
    add rbx, r8
    mov al, [rsi + rbx]
    cmp al, '#'
    je .fin

    mov al, 'P'
    mov [rsi + rbx], al

    sub rbx, r8
    mov al, '.'
    mov [rsi + rbx], al
    jmp .fin

.fin:
    pop rbp
    pop rdi
    pop rsi
    pop rbx
    ret
