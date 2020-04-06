;------------------------------------------------
;definición del segmento de pila
pila segment stack 'stack'
	db 128h dup ('pila')
pila ends

;------------------------------------------------
;definición del segmento de datos
datos segment 'data'
	numero dw 23456d
	cadena db 6 dup(' ')
datos ends

;------------------------------------------------
;definición del segmento de código
codigo segment 'code'

;----------------------------
main PROC FAR
	assume cs:codigo, ds:datos, ss:pila
	mov ax,datos
	mov ds,ax

	mov ax,numero
	mov bx,5    ;desplz sobre la cadena
	mov si,10   ;base

	bucle:
		sub dx,dx
		div si
		add dl,'0'
		dec bx
		mov byte ptr cadena[bx],dl
		or ax,ax
		jnz bucle
	mov byte ptr cadena[5],'$'

	;mostrar la cadena creada
	mov dx,OFFSET cadena
	mov ah,9
	int 21h

	mov ax,4C00h
	int 21h
main ENDP

codigo ENDS
END main
