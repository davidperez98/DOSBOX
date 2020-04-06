        ; MACRO QUE CAMBIA LOS ATRIBUTOS DE LOS CARACTERES EN PANTALLA (MODO TEXTO)
	; NO BORRA LO QUE HAYA EN PANTALLA, SOLO CAMBIA LA FORMA DE MOSTRARLOS
	
cambia_color MACRO atributo
	local bucle
	mov cx,2000
	mov ax,0b800h
	mov es,ax
	mov al,atributo
	mov si,1
	bucle:
		mov es:	[si],al
		add si,2
		loop bucle
ENDM
	
pila segment stack 'stack'
	dw 100h dup (?)
pila ends

datos segment 'data'
datos ends

codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		cambia_color 01000000b ; fondo rojo
                ;si usamos el atributo 01000100b pone tambi‚n el caracter
                ;en rojo, por lo que todo se ver  rojo (y no negro sobre rojo)
		mov ah,1	; hacemos una pausa
		int 21h
	
		cambia_color 00100000b ; fondo verde
		mov ah,1	; hacemos una pausa
		int 21h

		cambia_color 00010000b ; fondo azul
		mov ah,1	; hacemos una pausa
		int 21h
	
		cambia_color 00000111b ; fondo negro, letras blancas

                mov ax, 4C00h
		int 21h
	main ENDP
codigo ends

END main


; cada caracter representado en pantalla corresponde a 2 bytes contiguos
; en la memoria de pantalla: uno para la letra y otro para el atributo de
; color. Cada uno de los 8 bits del atributo corresponde a una caracteristica del atributo:
;
; bit 7º : parpadeo
; bit 6º : componente rojo del fondo
; bit 5º : componente verde del fondo
; bit 4º : componente azul del fondo
; bit 3º : intensidad 
; bit 2º : componente rojo del carácter
; bit 1º : componente verde del carácter
; bit 0º : componente azul del carácter

