;MACRO pausa_tecla
;espera la pulsacion de una tecla
pausa_tecla MACRO
        push ax
        mov ah,0   ;funcion para leer una tecla
        int 16h    ;interrupcion BIOS para teclado
        pop ax
ENDM

;MACRO modo_video
;cambia el modo de video (1 -- texto 40x25 color)
modo_video MACRO modo
        push ax
        mov al,modo
        mov ah,0
        int 10h
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

		modo_video 1

		mov dx,OFFSET msg_pulsa_tecla
		mov ah,9
		int 21h
		pausa_tecla

		modo_video 2

		mov ax,4C00h	; terminar y salir al S.O.
		int 21h

	main ENDP
codigo ends

END main
