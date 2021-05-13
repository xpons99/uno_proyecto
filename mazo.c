#include <stdio.h>
#include "mazo.h"
#include "azar.h"
#include "colores.h"

//Inicializa el mazo ORDENADO
void inicializar_mazo(t_mazo *p_mazo){
	int i=0, j, palo = 0;	
	
	while (i<CARTAS_CON_COLOR){	
		for(j=1;j<=MAX_COLOR;j++){
				
			inicializar_carta (&p_mazo->v[i], palo, j);
			i++;
		}
		palo++;
		if (palo>SKIP){
			palo = 1;	
		}
	}
	palo = WILD;
	while (i<MAX){
		inicializar_carta(&p_mazo->v[i], palo, WHITE);
		palo++;
		if (palo > WILD_DRAW)
			palo = WILD;
		i++;
	}
	p_mazo->num_cartas = i;
}

//Esta funcion baraja el MAZO para dejarlo DESORDENADO
void inicializar_mazo_desordenado (t_mazo *p_mazo){
	int num, i;
   	t_carta aux;
	 
   for (i=0; i<p_mazo->num_cartas; i++){
   		do{
   			num = numero_al_azar(p_mazo->num_cartas);
   		}while(i == num);
   		aux = p_mazo->v[i];
   		p_mazo->v[i] = p_mazo->v[num];
   		p_mazo->v[num] = aux;
	}
}

//Esta funcion roba una carta del mazo (baraja) y devuelve dicha carta
t_carta robar_carta(t_mazo *p_mazo){
	int i, cartas;
	t_carta carta;

	carta = p_mazo->v[0];
	cartas = p_mazo->num_cartas;
	
	for(i=0;i<cartas-1;i++){
		p_mazo->v[i]=p_mazo->v[i+1];
				
	}
	p_mazo->num_cartas--;	

	return carta;
}

//INICIALIZA el MAZO DE DESCARTES
void inicializar_mazo_descartes(t_mazo *p_mazo, t_mazo *p_descartes){
	int i, pos, trobat= 0;
	
	p_descartes->num_cartas = 0;

	while(trobat==0){		
		pos = numero_al_azar(p_mazo->num_cartas);
		if (p_mazo->v[pos].palo <= 9){
			trobat=1;
		}
	}
	p_descartes->v[0] = p_mazo->v[pos];
	for (i = pos; i<p_mazo->num_cartas-1; i++){
		p_mazo->v[i] = p_mazo->v[i+1];
	}
	p_mazo->num_cartas--;
	p_descartes->num_cartas++;
}

//Imprime el mazo en el modo COMPROBACION (MUESTRA TODAS LAS CARTAS)
void imprimir_mazo(t_mazo mazo){
	int i, j, sl = 0;
	for (i=0; i<mazo.num_cartas; i++){
		if (sl==SALTO_LINEA){
			printf("|\n ");
			for (j=0; j<20; j++){
				printf("---+");
			}
			printf("\n|");
			imprimir_carta(mazo.v[i]);
			sl = 1;
		}
		else{
			printf("|");
			imprimir_carta(mazo.v[i]);
			sl++;
		}	
	}
	printf("|");
}

//Imprime el MAZO DE DESCARTES 
void imprimir_mazo_desc(t_mazo descartes){
	printf("Mazo descartes:\n|");
	imprimir_carta(descartes.v[0]);
	printf("|(%d)" ,descartes.num_cartas);
}

/*Esta funcion IMPRIME por pantalla el MAZO (baraja) en el modo NO COMPROBACION
(SOLO MUESTRA UNA CARTA "TAPADA" Y EL NUMERO DE CARTAS DEL MAZO*/
void imprimir_mazo_no_comp(t_mazo mazo){	
	int i;
	printf("|");
	cambiar_color_fondo(WHITE);
	cambiar_color_letra(RED);
	printf("UNO");
	default_attributes();
}

//Esta funcion actualiza el mazo, dejando en la primera posicion la carta TIRADA
void actualizar_mazo_desc(t_carta tirada,t_mazo *p_descartes){
	int i;
	p_descartes->num_cartas++;
	for(i=p_descartes->num_cartas;i>=0;i--){
		p_descartes->v[i+1] = p_descartes->v[i];
	}
	p_descartes->v[0]=tirada;
}

//Esta funcion rellena el mazo cuando se queda sin cartas
void rellenar_mazo (t_mazo *mazo, t_mazo *descartes){
	int i, j=0, num_cartas;
	
	num_cartas = descartes->num_cartas;
	
	for (i=1; i<num_cartas; i++){
		mazo->v[j] = descartes->v[i];
		j++;
		mazo->num_cartas++;
		descartes->num_cartas --;
	}
	inicializar_mazo_desordenado(mazo);
}
	
