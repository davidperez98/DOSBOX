;definición del segmento de pila
pila segment stack 'stack'
	db 128h dup ('pila')
pila ends

;------------------------------------------------
;definición del segmento de datos
datos segment 'data'
        numero dw 89
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
        mov bx,10
	call escribir_numero

	mov ax,4C00h
	int 21h
main ENDP

;----------------------------
;subrutina recursiva para mostrar un número por pantalla
escribir_numero PROC NEAR
	push ax
	push dx

	mov dl,al
        cmp ax,bx
	jb escribir_resto
	sub dx,dx
        div bx
	call escribir_numero

    escribir_resto:
	add dl,'0'
	mov ah,2
	int 21h

	pop dx
	pop ax
	ret
escribir_numero ENDP

codigo ends
END main
