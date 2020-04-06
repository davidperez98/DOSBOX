#include <dos.h>

#define BYTE unsigned char

BYTE FG_COLOR = 7;   // Color del texto. Por defecto sera el 7 (gris claro)
BYTE BG_COLOR = 0; // Color de fondo. Por defecto sera el 0 (negro)
int ALTO = 24; // Alto de la consola
int ANCHO = 79; // Ancho de la consola

// (1)
/**############################################################################################
 * @brief Indica si se ha pulsado alguna tecla
 *
 * La funcion llama a la subfuncion 1 de la interrupcion numero 16. Una
 * vez llamada, devuelve el registro cflag (zero flag), en el cual se
 * almacena un 0 si se ha pulsado una tecla y un 1 en caso contrario.
 *
 * @return devuelve el valor del registro zero flag
 ############################################################################################*/

int kbhit(){
   union REGS inregs, outregs;

   // En el registro ah introducimos la subfuncion de la rutina que queremos, en este 
   //caso, es "deteccion de tecla pulsada en bufer de teclado"
   inregs.h.ah = 0x01;

   // Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina 
   //de "gestion del teclado"
   int86(0x16, &inregs, &outregs);

   return outregs.x.cflag;
} 

// (2)
/**############################################################################################
 * @brief Indica la posición x actual del cursor
 *
 * La funcion llama a la subfuncion 3 de la interrupcion numero 10. Una
 * vez llamada, devuelve el registro dl, en el cual se
 * almacena la columna actual donde se encuentra el cursor.
 *
 * @return devuelve el valor del registro dl
 ############################################################################################*/

int whereX(){
   union REGS inregs, outregs;

   // En el registro ah introducimos la subfuncion de la rutina que queremos, 
   //en este caso, es "obtener tamaño y posicion del cursor"
   inregs.h.ah = 0x03;
   inregs.h.bh = 0x00;

   // Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina 
   //de "comunicacion con la tarjeta de video"
   int86(0x10, &inregs, &outregs);

   return outregs.h.dl;

}

// (3)
/**############################################################################################
 * @brief Indica la posición y actual del cursor
 *
 * La funcion llama a la subfuncion 3 de la interrupcion numero 10. Una
 * vez llamada, devuelve el registro dh, en el cual se
 * almacena la fila actual donde se encuentra el cursor.
 *
 * @return devuelve el valor del registro dh
 ############################################################################################*/

int whereY(){
   union REGS inregs, outregs;

   // En el registro ah introducimos la subfuncion de la rutina que queremos, 
   //en este caso, es "obtener tamaño y posicion del cursor"
   inregs.h.ah = 0x03;
   inregs.h.bh = 0x00;

   // Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con 
   // la rutina de "comunicacion con la tarjeta de video"
   int86(0x10, &inregs, &outregs);

   return outregs.h.dh;

}

// (4)
/**############################################################################################
 * @brief Mueve el cursor a una posicion determinada
 *
 * La funcion llama a la subfuncion 2 de la interrupcion numero 10. Dicha subfuncion
 * mueve el cursor a la posicion que se le indique
 *
 * @param x Indica la columna donde se quiere colocar el cursor
 * @param y Indice la fila donde se quiere colocar el cursor
 ############################################################################################*/

void gotoxy(int x, int y){
   union REGS inregs, outregs;

   // En el registro ah introducimos la subfuncion de la rutina que queremos, 
   // en este caso, es "colocar el cursor en una posicion determinada"
   inregs.h.ah = 0x02;

   // En el registro dx introducimos la fila y la columna donde queremos colocar el cursor
   inregs.h.bh = 0x00;
   inregs.h.dh = y;
   inregs.h.dl = x;

   // Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la 
   //rutina de "comunicacion con la tarjeta de video"
   int86(0x10, &inregs, &outregs);

}

// (5)
/**############################################################################################
 * @brief Fija el aspecto del cursor, debe admitir tres valores: INVISIBLE, NORMAL y GRUESO
 *
 * La funcion llama a la subfuncion 1 de la interrupcion numero 10. Dicha subfuncion
 * fija el aspecto del cursor en funcion de los numeros de linea que se le indiquen
 *
 * @param tipo_cursor Indica el tipo de cursor que desea establecer. (INVISIBLE,NORMAL o GRUESO)
 ############################################################################################*/

void setcursortype(enum types tipo_cursor){
   union REGS inregs, outregs;

   // En el registro ah introducimos la subfuncion de la rutina que queremos, 
   // en este caso, es "fijar el tamaño del cursor en modo texto"
   inregs.h.ah = 0x01;

   switch(tipo_cursor){
      case NORMAL:
         inregs.h.ch = 010;
         inregs.h.cl = 010;
         break;
      case GRUESO:
         inregs.h.ch = 000;
         inregs.h.cl = 010;
         break;
      case INVISIBLE:
         inregs.h.ch = 010;
         inregs.h.cl = 000;
         break;
   }

   // Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia 
   //con la rutina de "comunicacion con la tarjeta de video"
   int86(0x10, &inregs, &outregs);
}

// (6)
/**############################################################################################
 * @brief Fija el modo de video deseado
*
* La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion
* fija el modo de video que se le indique.
*
* @param modo Es un caracter que indica el modo que se desea. Dicho caracter se debe traducir 
              al decimal adecuado
 ############################################################################################*/

void setvideomode(BYTE modo){
   union REGS inregs, outregs;

   inregs.h.ah = 0x00;
   inregs.h.al = modo;
   int86(0x10,&inregs,&outregs);
} 

// (8)
/**############################################################################################
* @brief Modifica el color de primer plano con que se mostrarán los caracteres
*
* La funcion modifica la variable global FG_COLOR, la cual almacena el color en el que
* se escribe el texto por consola.
 ############################################################################################*/

void textcolor(int color){
   FG_COLOR = color;  // La funcion modifica la variable global FG_COLOR, la cual almacena el 
                  // color en el que se escribe el texto por consola.
}

// (9)
/**############################################################################################
* @brief Modifica el color de fondo con que se mostrarán los caracteres
*
* La funcion modifica la variable global BG_COLOR, la cual almacena el color en el que
* se escribe el fondo de los caracteres por consola.
 ############################################################################################*/

void textbackground(int color){
   BG_COLOR = color; // La funcion modifica la variable global BG_COLOR, la cual almacena el 
                  // color de fondo de la consola  
} 

// (10)
/**############################################################################################
* @brief Borra toda la pantalla
*
* Esta funcion borra toda la pantalla haciendo que la funcion scrollup deslice la pantalla
* hacia arriba tantas lineas como alto tenga la consola. Ademas, situa el cursor en la posicion 0,0.
 ############################################################################################*/

void clrscr(){
   int color = BG_COLOR << 4 | FG_COLOR;

   union REGS inregs, outregs;
   inregs.h.ah = 0x06; // subfuncion "desplazar zona de pantalla hacia arriba"
   inregs.h.al = ALTO+1; // núm. lineas
   inregs.h.bh = color;
   inregs.h.ch = 0;
   inregs.h.cl = 0;
   inregs.h.dh = ALTO;
   inregs.h.dl = ANCHO;

   // interrupcion 0x10 -> rutina de "comunicacion con la tarjeta de video"
   int86(0x10, &inregs, &outregs);

   gotoxy(0,0);
}

// (14)
/**############################################################################################
* @brief Escribe un caracter en pantalla con el color indicado actualmente
*
* La funcion llama a la subfuncion 9 de la interrupcion numero 10. Dicha subfuncion
* imprime un caracter por pantalla con el color indicado y el numero de veces que se desee.
* Finalmente avanza el cursor.
*
* @param caracter Caracter que se desea imprimir
* @param repeticiones Numero de veces que se desea imprimir el caracter
* @see avanzar_cursor
 ############################################################################################*/

void cputchar(const char c, int repeticiones){
   // Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
   // seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
   union REGS inregs, outregs;
   int color = BG_COLOR << 4 | FG_COLOR;

   // En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "escribir un caracter en pantalla"
   inregs.h.ah = 0x09;

   // En el resto de registros se introducen el caracter, el color y el numero de veces que se desea imprimir el caracter
   inregs.h.al = c;
   inregs.h.bl = color;
   inregs.h.bh = 0x00;
   inregs.x.cx = repeticiones;

   // Mediante la funcion int86 llamamos a la interrupcion 0x10 que se asocia con la rutina de "comunicacion con la tarjeta de video"
   int86(0x10, &inregs, &outregs);

   // Finalmente avanzamos el cursor
   //avanzar_cursor();
}

// (15)
/**############################################################################################
* @brief Obtiene el caracter de teclado y lo muestra en pantalla
*
* La funcion llama a la subfuncion 0 de la interrupcion numero 10. Dicha subfuncion
* lee un caracter desde el teclado y lo almacena en el registro al. En caso de ser
* una tecla especial queda almacenado en el ah.
*
* @return Decimal que representa el caracter introducido por teclado
 ############################################################################################*/
int migetche(){
   // Tenemos dos registros, uno donde almacenamos los parametros de la interrupcion
   // seleccionada y otro donde se guardan los datos devueltos por dicha interrupcion
   union REGS inregs, outregs;
   int caracter;

   // En el registro ah introducimos la subfuncion de la rutina que queremos, en este caso, es "leer un caracter desde el teclado"
   inregs.h.ah = 0x00;

   // Mediante la funcion int86 llamamos a la interrupcion 0x16 que se asocia con la rutina de "gestion del teclado"
   int86(0x16, &inregs, &outregs);

   // Si al es 0 significa que es un caracter especial. 1 en caso contrario
   if(outregs.h.al != 0)
      caracter = outregs.h.al;
   else
      caracter = outregs.h.ah;

   cputchar(caracter, 1);

   return caracter;
}


/*#################################################################################*/
int main(){

	int linea, columna, color;
   enum types tipo_cursor = NORMAL;

	// (1) khbit ###################################################
	   clrscr();
		cputs("PAC\n Pulse una tecla para continuar (prueba del kbhit):");
   	while(!kbhit());
   	cprintf("\r\nTecla pulsada...\r\n",getch());
	   getch();

	// (4) gotoxy ###################################################
	   gotoxy(5,10);
   	cprintf("Prueba del gotoxy, mostrando en la coordenada (5,10)");
   	getch();

      clrscr();
      gotoxy(0,0);

	// (5) setcursortype ###################################################
	   cputs("\nCursor invisible: ");
   	tipo_cursor = INVISIBLE;
   	setcursortype(tipo_cursor);
   	getch();
   	cputs("\nCursor grueso: ");
   	tipo_cursor = GRUESO;
   	setcursortype(tipo_cursor);
   	getch();
   	cputs("\nCursor normal: ");
   	tipo_cursor = NORMAL;
   	setcursortype(tipo_cursor);
   	getch();

	// (6) setvideomode ###################################################
	   setvideomode('d');
      cputs("Restituir modo de video");
      getch();
      setvideomode(3);
      clrscr();
      cputs("Pulse una tecla para finalizar\n");
      getch();
            
	// (8) textcolor ###################################################
	// (9) textbackground ###############################################
	   cputs("Cambiamos de color. FG=RED, BG=BLUE\n");
   	getch();
   	textcolor(4);
   	textbackground(1);
   	cputchar('P',1);
   	getch();
   	textcolor(7);	// COLOR DE FUENTE POR DEFECTO
   	textbackground(0); // FONDO AZUL PARA HACER EL CLEAR SCREAN
   	clrscr();

	// (10) clrscr ###################################################
	   cputs("Prueba del clrscr. Pulse una tecla para borrar la pantalla.\n");
   	getch();
   	clrscr();
   	cputs("Pantalla borrada. A partir de este punto voy a borrar la linea.\n");
   	

	// (11) clreol ###################################################
	   cputs("Pantalla borrada. A partir de este punto NO voy a borrar la linea.");
   	getch();
   	gotoxy(40,0);
   	clreol();
   	getch();
   	clrscr();

	// (14) cputchar ###################################################
   cputs("Prueba del cputchar\n");
   cputchar('P',1);

	return 0;
}