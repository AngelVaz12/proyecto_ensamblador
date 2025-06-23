section .text
    global funciones_laberinto       ; Hacemos pública la función para que sea visible desde C

funciones_laberinto:
    ; rcx = puntero al mapa (char *mapa)
    ; rdx = número de renglones
    ; r8  = número de columnas
    ; r9  = tecla presionada

    ; GUARDAMOS REGISTROS QUE VAMOS A MODIFICAR
    push rbx
    push rsi
    push rdi

    ; INICIALIZACIONES
    mov rsi, rcx      ; rsi = mapa (puntero base)
    xor rbx, rbx      ; rbx = índice lineal, inicia en 0
    imul rdx, r8      ; rdx = renglones * columnas (tamaño total del mapa)
    mov dil, r9b      ; dil = tecla presionada (extraída del registro r9b → parte baja de r9)

;-------------------------------
; BUSCAR POSICIÓN DEL JUGADOR 'P'
;-------------------------------
buscar:
    cmp rbx, rdx           ; ¿ya recorrimos todo el mapa?
    jge fin                ; si sí, terminamos

    mov al, [rsi + rbx]    ; cargamos el valor del mapa en la posición rbx
    cmp al, 'P'            ; ¿es la posición actual del jugador?
    je mover               ; si sí, vamos a calcular el movimiento

    inc rbx                ; si no, pasamos a la siguiente posición
    jmp buscar             ; repetir

;-------------------------------
; IDENTIFICAR DIRECCIÓN A MOVER
;-------------------------------
mover:
    mov rax, 0             ; rax será el desplazamiento
    cmp dil, 'd'
    je .derecha
    cmp dil, 'a'
    je .izquierda
    cmp dil, 'w'
    je .arriba
    cmp dil, 's'
    je .abajo
    jmp fin                ; si no fue ninguna tecla válida, salir

.derecha:
    mov rax, 1             ; desplazamiento +1
    jmp verificar

.izquierda:
    mov rax, -1            ; desplazamiento -1
    jmp verificar

.arriba:
    neg r8                 ; cambiamos signo para hacer -columnas
    mov rax, r8            ; desplazamiento = -número de columnas
    neg r8                 ; restauramos r8 a valor original
    jmp verificar

.abajo:
    mov rax, r8            ; desplazamiento = número de columnas
    jmp verificar

;-------------------------------
; VERIFICAR CASILLA DESTINO
;-------------------------------
verificar:
    mov rdi, rbx           ; rdi = posición actual
    add rdi, rax           ; rdi = nueva posición (destino)
    mov al, [rsi + rdi]    ; leemos el carácter en el destino

    cmp al, '#'            ; ¿es una pared?
    je fin                 ; si es pared, salir sin mover

    cmp al, 'X'            ; ¿es la meta?
    je gano                ; si es la meta, ir a bloque de victoria

    ; MOVIMIENTO NORMAL
    mov byte [rsi + rdi], 'P'  ; colocamos 'P' en la nueva posición
    mov byte [rsi + rbx], '.'  ; dejamos '.' en la posición anterior
    jmp no_gano

;-------------------------------
; GANÓ EL JUGADOR
;-------------------------------
gano:
    mov byte [rsi + rdi], 'P'  ; colocamos 'P' sobre la meta
    mov byte [rsi + rbx], '.'  ; limpiamos posición anterior
    mov eax, 1                 ; señalamos que ganó (valor de retorno)
    jmp salir

;-------------------------------
; NO GANÓ → REGRESAMOS 0
;-------------------------------
no_gano:
    xor eax, eax               ; eax = 0 (no ganó)

;-------------------------------
; FIN NORMAL (SIN MOVIMIENTO)
;-------------------------------
fin:
    xor eax, eax               ; eax = 0 (por defecto, si no se mueve)

;-------------------------------
; SALIDA Y RESTAURACIÓN
;-------------------------------
salir:
    pop rdi                    ; restaurar rdi
    pop rsi                    ; restaurar rsi
    pop rbx                    ; restaurar rbx
    ret                        ; regresar a C
