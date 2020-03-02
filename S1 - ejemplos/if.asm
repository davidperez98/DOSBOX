pila segment stack 'stack'
	dw 100h dup (?)
pila ends

datos segment 'data'
        msg_if   db 10,13,'parte del IF$'
        msg_else db 10,13,'parte del ELSE$'
datos ends

codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax


                mov ax,7
                mov bx,3

                cmp ax,bx       ; comprobar si son iguales
                jne instr_else
                instr_if:
                   mov dx,OFFSET msg_if
                   mov ah,9
                   int 21h
                   jmp fin_ifelse
                instr_else:
                   mov dx,OFFSET msg_else
                   mov ah,9
                   int 21h
                fin_ifelse:

		mov ax,4C00h
		int 21h
	main ENDP
codigo ends

END main
