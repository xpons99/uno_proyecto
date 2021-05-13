#include <stdio.h>
#include "jugador.h"
#include "azar.h"
#include "mazo.h"

//Esta funcion inicializa el mazo. Devuelve el mazo inicializado
t_mazo inicializar_mano (t_mazo *p_mano){
	
	int i;
	t_jugador jug;
	
	jug.mano.num_cartas = MANO;
	
	for (i=0; i<MANO; i++){
		 jug.mano.v[i] = robar_carta(p_mano);
	}
	return jug.mano;
}

/*Esta funcion calcula las jugadas posibles que tiene un jugador, comparando las cartas de la mano con la carta del mazo descartes (si NO es una carta ESPECIAL)
  devuelve un vector de cartas, con las jugadas posibles*/
t_mazo calcular_jugadas_posibles(t_mazo mano, t_mazo desc){
	
	int i, j=0, trobat=0, trobat2=0, pos=0;
	t_mazo posibles;

	for(i=0;i<mano.num_cartas;i++){
		if(mano.v[i].color==desc.v[0].color || mano.v[i].palo==desc.v[0].palo || mano.v[i].palo ==WILD){
			posibles.v[j]=mano.v[i];
			j++;
		}
		else if (mano.v[i].palo == WILD_DRAW){
			trobat = 1;
			pos = i;
		}
	}
	posibles.num_cartas = j;
	if (trobat == 1){
		for (i=0; i<posibles.num_cartas; i++){
			if(desc.v[i].color == posibles.v[i].color){
				trobat2=1;
			}
		}
		if (trobat2==0){
			posibles.num_cartas++;
			posibles.v[posibles.num_cartas-1] = mano.v[pos];
		}
	}
	return posibles;
}

//Esta funcion devuelve la carta que el jugador en TURNO quiere tirar del mazo de las JUGADAS POSIBLES	
t_carta escoger_carta (int turno, t_mazo posibles){ 
	int seleccion;
	t_carta escogida;
	
	if (turno == JUGADOR){
		seleccion = preguntar_n_en_rango("\nQue carta tiras?", 0, posibles.num_cartas-1);
	}
	else{
		seleccion = numero_al_azar(posibles.num_cartas);
	}
	escogida = posibles.v[seleccion];
	return escogida;
}

//Esta funcion MUESTRA las JUGADAS POSIBLES	
void mostrar_jugadas_posibles (int turno, t_mazo posibles, int comp){
	int i;
	if (turno == JUGADOR || comp != 0){
		printf("Jugadas posibles: ");
		for (i=0; i<posibles.num_cartas; i++){
			printf("%d(|", i);
			imprimir_carta(posibles.v[i]);
			printf("|) ");
		}
	}
}

//Esta funcion ELIMINA la CARTA TIRADA de la MANO
void eliminar_carta_mano(t_jugador *p_jugador, t_carta tirada){
	int i, pos;
	
	for(i=0;i<p_jugador->mano.num_cartas;i++){
		if(p_jugador->mano.v[i].color==tirada.color && p_jugador->mano.v[i].palo==tirada.palo){
			pos=i;
		}
	}
	for (i=pos; i<=p_jugador->mano.num_cartas; i++){
		p_jugador->mano.v[i] = p_jugador->mano.v[i+1];
	}

	p_jugador->mano.num_cartas--;
	mostrar_uno(p_jugador->mano);
}

//Esta funcion MUESTRA la CARTA TIRADA
void tirar_carta (t_carta tirada){
	printf("Tira: |");
	imprimir_carta(tirada);
	printf("|");
}

//Esta función comprueba que el jugador tenga cartas por tirar, devuelve FALSE si no puede tirar y TRUE en caso contrario
int tiene_por_tirar(t_mazo posibles){
	if(posibles.num_cartas==0){
		return FALSE;
	}else{
		return TRUE;
	}
}

//Esta funcion anyade una CARTA a la MANO
void anyadir_carta_mano(t_carta carta, t_mazo *p_mano){
	p_mano->num_cartas++;
	p_mano->v[p_mano->num_cartas-1]=carta;
}

//Esta funcion IMPRIME la MANO 
void imprimir_mano(t_mazo mano){
	int i;
	for (i=0; i<mano.num_cartas; i++){
		printf("|");
		imprimir_carta(mano.v[i]);
	}
	if(mano.num_cartas>0){
 		printf("|");
	}
	mostrar_uno(mano);
}

//Esta funcion IMPRIME el NOMBRE del JUGADOR por PANTALLA
void imprimir_nombre(t_jugador jug){
	printf("%s:", jug.nombre);
}

/*Esta funcion calcula las jugadas posibles que tiene un jugador, comparando las cartas de la mano con el color que se ha elegido al tirar una carta ESPECIAL
Devuelve un vector de cartas, con las jugadas posibles*/
t_mazo calcular_jugadas_posibles_especiales(t_mazo mano, int color){
	int i, j=0, trobada =0, trobada2=0, pos = 0;
	t_mazo posibles_especiales;

	for(i=0;i<mano.num_cartas;i++){
		if(mano.v[i].color==color || mano.v[i].palo == WILD){
			trobada = 1;
			posibles_especiales.v[j]=mano.v[i];
			j++;
		}else if (mano.v[i].palo == WILD_DRAW){
			trobada2=1;
			pos = i;
		}
	}
	if (trobada == 0 && trobada2 == 1){
		posibles_especiales.v[0] = mano.v[pos];
		j++;
	}
	posibles_especiales.num_cartas = j;
	return posibles_especiales;
}

/*Esta funcion MUESTRA por PANTALLA **UNO** en el caso que el jugador solo tenga una carta
o se quede con una al tirar*/
void mostrar_uno (t_mazo mano){
	if(mano.num_cartas==1){ 
		cambiar_color_letra(GREEN);
		printf("** UNO **");
		default_attributes();
	}
}
