#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;

int txt_color = 0;
int bcg_color = 0;
int num_columnas = 0;

// hace una pausa
void pausa(){
	 union REGS inregs, outregs;
	 inregs.h.ah = 0x00;
	 int86(0x16, &inregs, &outregs);
}

// pone un pixel en la coordenada X,Y de color C
void pixel(int x, int y, BYTE C){
	 union REGS inregs, outregs;
	 inregs.x.cx = x;
	 inregs.x.dx = y;
	 inregs.h.al = C;
	 inregs.h.ah = 0x0C;
	 int86(0x10, &inregs, &outregs);
}

// pone el cursor en una posicion determinada
void migotoxy(int x, int y){
	union REGS inregs, outregs;
	inregs.h.ah = 0x02;
	inregs.h.dl = x;
	inregs.h.dh = y;
	inregs.h.bh = 0;
	int86(0x10, &inregs, &outregs);
}

// fija el aspecto del cursor
void misetcursortype(int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

// fija el modo de video deseado
void misetvideomode(BYTE mode){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = mode;
	int86(0x10, &inregs, &outregs);
}

// averigua el modo de video actual
void migetvideomode(BYTE* al, int* ah){
	union REGS inregs, outregs;
	inregs.h.ah = 0x0F;
	int86(0x10, &inregs, &outregs);
	*al = outregs.h.al;
	printf("\nComprobacion --> *al = %d\n", *al);
	if(*al<04 || *al==07){
		*ah = outregs.h.ah;
	}else{
		*ah = 0;
	}
}

// modifica el color de primer plano con que se mostraran los caracteres
void mitextcolor(int color){
	txt_color = color;
}

// modifica el color de fondo con que se mostraran
void mitextbackground(int color){
	bcg_color = color;
}

// borra toda la pantalla en modo texto
void miclrscr(){
	if(num_columnas > 0){
		union REGS inregs, outregs;
		printf("\nHa entrado bien\n");
		inregs.h.ah = 0x06;
		inregs.h.al = 0;
		inregs.h.ch = 0;
		inregs.h.cl = 0;
		inregs.h.dh = 25;
		inregs.h.dl = num_columnas;
		int86(0x10, &inregs, &outregs);
	}else{
		printf("\nHa entrado fatal\n");
	}
}

// escribe un caracter en pantalla con el color indicado actualmente
void micputchar(char c, int repeticiones){
	union REGS inregs, outregs;

	int color = (bcg_color << 4) | txt_color;

	inregs.h.ah = 0x09;
	inregs.h.al = (int) c;
	inregs.h.bl = color;
	inregs.h.bh = 0x00;
	inregs.x.cx = repeticiones;

	int86(0x10, &inregs, &outregs);
}

// obtiene un caracter de teclado y lo muestra en pantalla
int migetche(){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;
	int86(0x21, &inregs, &outregs);
	return outregs.h.al;
}

/*#################################################################################*/
int main(){
	// para migetvideomode()
	BYTE al_tmp;
	int ah_tmp;
	// para migetche()
	int aux;
	
	misetvideomode(MODOGRAFICO);
	misetvideomode(MODOTEXTO);

	printf("\nmigotoxy(1,1)\n");
	migotoxy(1, 1);
	pausa();

	printf("\nmisetcursortype(1)\n");
	misetcursortype(1);
	pausa();

	printf("\nmisetcursortype(2)\n");
	misetcursortype(2);
	pausa();

	printf("\nmisetcursortype(3)\n");
	misetcursortype(3);
	pausa();

	printf("\nmisetvideomode(MODOGRAFICO)\n");
	pausa();
	misetvideomode(MODOGRAFICO);
	pixel(10,40,0);
	pixel(10,50,1);
	pixel(15,60,2);
	pixel(20,70,3);
	pausa();
	misetvideomode(MODOTEXTO);
	
	printf("\nComprobacion --> num_columnas = %d\n", num_columnas);

	printf("\nmigetvideomode()\n");
	migetvideomode(&al_tmp, &ah_tmp);
	printf("al_tmp: %d\n", al_tmp);
	printf("ah_tmp: %d\n", ah_tmp);
	num_columnas = ah_tmp;	
	pausa();

	printf("\nmicputchar(z, 3)/mitextcolor(2)\n");
	mitextcolor(2);
	micputchar('z', 3);
	pausa();

	printf("\nmicputchar(z, 3)/mitextbackground(3)\n");
	mitextbackground(3);
	micputchar('z', 3);
	pausa();

	printf("\nmiclrscr()\n");
	miclrscr();
	pausa();

	printf("\nmigetche()\n");
	aux = migetche();
	printf("%d\n", aux);
	pausa();

	return 0;
}
