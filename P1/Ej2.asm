VERDE   EQU 1
BLANCO  EQU 3

;MACRO pausa_tecla
;espera la pulsacion de una tecla
pausa_tecla MACRO
        push ax
        mov ah,0   ;funcion para leer una tecla
        int 16h    ;interrupcion BIOS para teclado
        pop ax
ENDM

;MACRO modo_video
;cambia el modo de video (4 -- grafico 320x200 4 colores CGA)
modo_video MACRO modo
        push ax
        mov al,modo
        mov ah,0
        int 10h
        pop ax
ENDM

;MACRO pixel
;pone un pixel en la coordenada X,Y de color C
pixel MACRO X,Y,C
        push ax
        push cx
		push dx
		mov ax,Y
		mov cx,X
		mov dx,ax
        mov al,C
        mov ah,0Ch
        int 10h
        pop dx
        pop cx
		pop ax
ENDM

pila segment stack 'stack'
	dw 100h dup (?)
pila ends

datos segment 'data'
		msg_pulsa_tecla db 'pulsa para continuar...',7,'$'
datos ends


codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		modo_video 4

		;pintar una linea horizontal
		mov cx,320
		bucle11:
			pixel cx,10,VERDE
			dec cx
			jnz bucle11
		mov cx,320
		bucle12:
			pixel cx,190,VERDE
			dec cx
			jnz bucle12

		;pintar una linea vertical
		mov cx,200
		bucle21:
			pixel 10,cx,VERDE
			dec cx
			jnz bucle21
		mov cx,200
		bucle22:
			pixel 310,cx,VERDE
			dec cx
			jnz bucle22

		pixel 142,98,BLANCO    ; puntos blancos
		pixel 62,70,BLANCO
		pixel 42,20,BLANCO

		pausa_tecla

		modo_video 2

		mov ax,4C00h	; terminar y salir al S.O.
		int 21h

	main ENDP
codigo ends

END main
