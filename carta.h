#ifndef CARTA_H
#define CARTA_H
#define MAX_COLOR 4
#define DRAW_2 10 	//carta Robar 2
#define REVERSE 11	//carta Cambiar sentido
#define SKIP 12		//carta pasar turno
#define WILD 13		//carta Cambiar color
#define WILD_DRAW 14	//carta Cambiar color + Robar 4
typedef struct
{
	int palo;
	int color;

}t_carta;

void inicializar_carta (t_carta *carta, int palo, int color);
void imprimir_carta (t_carta carta);

#endif
