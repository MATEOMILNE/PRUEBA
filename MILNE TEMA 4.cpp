#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 15
#define MAX_POZOS 2
#define MAX_COMODINES 2

char tablero[BOARD_SIZE][BOARD_SIZE];
int equipoTortuga = 1;
int equipoLiebre = 2;
int tortugaPosX = 0;
int tortugaPosY = 0;
int liebrePosX = 0;
int liebrePosY = 0;
int tortugaPozos = 0;
int liebrePozos = 0;
int tortugaComodines = 0;
int liebreComodines = 0;

// Inicio del  tablero con "X"
void inicializarTablero() { /*void inicializarTablero(): Esta función se encarga de inicializar el tablero del juego. Establece todas las posiciones del tablero con la letra "X".*/
    int i, j;
    for (i=0;i<BOARD_SIZE;i++) 
	{
        for (j=0;j<BOARD_SIZE;j++) 
		{
            tablero[i][j] = 'X';
        }
    }
}

// Imprime el tablero 
void imprimirTablero() { /* void imprimirTablero(): Esta función imprime el tablero actual en la consola. Recorre las filas y columnas del tablero y muestra el contenido de cada casilla. */
    int i, j;
    for (i=0;i<BOARD_SIZE;i++)
	 {
        for (j=0;j<BOARD_SIZE;j++)
	    {
            printf("%c ", tablero[i][j]);
        }
        printf("\n");
    }
}

// Carga un elemento (pozo o comodín) en una posición aleatoria del tablero
void cargarElementoAleatorio(char elemento) { 	/*void cargarElementoAleatorio(char elemento): Esta función carga un elemento (pozo o comodín) en una posición aleatoria del tablero. Recibe como parámetro el elemento que se desea cargar.*/
    int posX, posY;
    do {
        posX=rand() % BOARD_SIZE;
        posY=rand() % BOARD_SIZE;
    } 
	while (tablero[posX][posY]!='X');
    tablero[posX][posY]=elemento;
}

// Coloca un equipo en una posición específica del tablero
void colocarEquipo(int equipo, int posX, int posY) {	/*void colocarEquipo(int equipo, int posX, int posY): Esta función coloca un equipo (tortuga o liebre) en una posición específica del tablero. Y tiene en cuenta el número de equipo (1 para tortuga, 2 para liebre) y las coordenadas X e Y donde se colocará el equipo.*/
    if (equipo == equipoTortuga)
	 {
        tablero[posX][posY]='T';
        tortugaPosX=posX;
        tortugaPosY=posY;
    }
	 else if (equipo==equipoLiebre)
	  {
        tablero[posX][posY]='L';
        liebrePosX=posX;
        liebrePosY=posY;
      }
}

// realiza el lanzamiento de un dado y devuelve el resultado
int lanzarDado() 
{
    return (rand() % 6)+1;
}

// Mueve un equipo en el tablero según la cantidad de pasos obtenida en el dado
void moverEquipo(int equipo, int cantidadPasos) {		/*void moverEquipo(int equipo, int cantidadPasos): Esta función se encarga de mover un equipo en el tablero según la cantidad de pasos obtenida en el dado. Recibe como parámetros el número de equipo (1 para tortuga, 2 para liebre) y la cantidad de pasos a mover.*/
    int i;
    int* posX;
    int* posY;
    if (equipo==equipoTortuga) 
	{
        posX = &tortugaPosX;
        posY = &tortugaPosY;
    } 
	
	else if (equipo==equipoLiebre) 
	{
        posX = &liebrePosX;
        posY = &liebrePosY;
    }

    for (i=0;i<cantidadPasos;i++) 
	{
        if (*posY<BOARD_SIZE-1) 
		{
            (*posY)++;
        }
		
		 else {
            (*posX)++;
        	  }
    }

    if (equipo==equipoLiebre)
	 {
        cantidadPasos *=2;
    }

    for (i=0;i<cantidadPasos;i++) 
	{
        if (*posY< BOARD_SIZE-1)
		 {
            (*posY)++;
        } else {
            (*posX)++;
        }
    }
}

// Verifica el tipo de casilla en una posición dada
// 0: Fuera del tablero, -1: Pozo, 1: Comodín, 2: Casilla vacía
int verificarCasilla(int posX, int posY) {
    if (posX>=BOARD_SIZE||posY>=BOARD_SIZE)
	 {
        return 0;  // Fuera del tablero
    }

    char casilla=tablero[posX][posY];
    if (casilla=='0') 
	{
        return -1;  // Cae en un pozo
    } 
	
	else if (casilla=='C') 
	{
        return 1;  // Cae en un comodin
    } 
	
	else {
        return 2;  // Casilla vacía
    }
}

// Función principal del juego
void jugar() {		/*void jugar(): maneja los turnos, lanza el dado, mueve los equipos y verifica las condiciones de victoria o derrota.*/
    int dado;
    int ganador = 0;
    int turno = 1;  // 1: Tortuga, 2: Liebre
    srand(time(NULL));

    // Configuración inicial del juego
    inicializarTablero();
    cargarElementoAleatorio('0');
    cargarElementoAleatorio('0');
    cargarElementoAleatorio('C');
    cargarElementoAleatorio('C');
    colocarEquipo(equipoTortuga, 0, 0);
    colocarEquipo(equipoLiebre, 0, 0);

    while (ganador==0) 
	{
        printf("\n=== Turno del Equipo %d ===(1- tortuga  2- liebre)\n", turno);
        printf("Presiona Enter para lanzar el dado.\n");
        getchar();

        dado=lanzarDado();
        printf("Resultado del dado: %d\n", dado);

        if(turno == equipoTortuga) 
		{
            moverEquipo(equipoTortuga, dado);
            int resultado = verificarCasilla(tortugaPosX, tortugaPosY);
            
			if(resultado==0) 
			{
                printf("La tortuga cayó en un pozo. Pierde el juego.\n");
                ganador=equipoLiebre;
            } 
            
			else if (resultado==1)
			 {
                printf("La tortuga encontró un comodin. Duplica su próxima jugada.\n");
                tortugaComodines++;
            }
			 else {
                colocarEquipo(equipoTortuga, tortugaPosX, tortugaPosY);
                
				if (tortugaPosX>=BOARD_SIZE || tortugaPosY>=BOARD_SIZE)
				 {
                    printf("La tortuga llegó a la meta. ¡Gana el juego!\n");
                    ganador = equipoTortuga;
                }
            }
        } 
		
		else if (turno==equipoLiebre)
		 {
            moverEquipo(equipoLiebre, dado);
            int resultado=verificarCasilla(liebrePosX,liebrePosY);
           
		    if (resultado==0)
			{
                printf("La liebre cayó en un pozo. Pierde el juego.\n");
                ganador=equipoTortuga;
                
            } 
            
			else if (resultado==1) 
			{
                printf("La liebre encontró un comodin. Avanza un casillero.\n");
                liebreComodines++;
            }
			 
			else {
                colocarEquipo(equipoLiebre, liebrePosX, liebrePosY);
               
			    if (liebrePosX>=BOARD_SIZE||liebrePosY>=BOARD_SIZE) 
				{
                    printf("La liebre llegó a la meta. ¡Gana el juego!\n");
                    ganador = equipoLiebre;
                }
            }
        }

        imprimirTablero();

        if (ganador == 0)
		 {
            turno=(turno==equipoTortuga)?equipoLiebre:equipoTortuga;
        }
    }

    // Resultado final del juego
    printf("\n=== Resultado Final ===\n");
    printf("Equipo Ganador: %d\n", ganador);
    printf("Pozos atravesados por la Tortuga: %d\n", tortugaPozos);
    printf("Pozos atravesados por la Liebre: %d\n", liebrePozos);
    printf("Comodines atravesados por la Tortuga: %d\n", tortugaComodines);
    printf("Comodines atravesados por la Liebre: %d\n", liebreComodines);
}

int main() 
{
    jugar();
    return 0;
}
