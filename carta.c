#include <stdio.h>
#include "carta.h"
#include "colores.h"

//Esta funcion INICIALIZA las CARTAS
void inicializar_carta (t_carta *carta, int palo, int color){
		carta->palo = palo;
		carta->color = color;
}

//Esta funcion IMPRIME las CARTAS
void imprimir_carta (t_carta carta){
	cambiar_color_fondo(carta.color);
	if (carta.palo >= 0 && carta.palo <= 9){	
		printf(" %d ", carta.palo);
	}
	else{
		switch (carta.palo){
			case DRAW_2:
 				printf("+2 ");
				break;
			case REVERSE:
				printf(" R ");
				break;
			case SKIP:
				printf(" S ");
				break;
			case WILD:
				cambiar_color_fondo(WHITE);
				cambiar_color_letra(BLACK);
				printf(" W ");
				cambiar_color_letra(WHITE);
				break;
			case WILD_DRAW:
				cambiar_color_fondo(WHITE);
				cambiar_color_letra(BLACK);
				printf("W+4");
				cambiar_color_letra(WHITE);
				break;
		}
	}
	default_attributes();
}
