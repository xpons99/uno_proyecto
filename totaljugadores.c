#include <stdio.h>
#include <string.h>
#include "totaljugadores.h"

//esta funcion INCIALIZA la MANO de TODOS los JUGADORES
void inicializar_mano_jugadores(t_mazo *p_mazo, t_jugadores *p_j){
	int i;
	for(i=0;i<p_j->num_jugadores;i++){
		p_j->jugador[i].mano = inicializar_mano (p_mazo);
	}
}

//esta funcion IMPRIME LA MANO de los JUGADORES CUANDO el MODO es NO COMPROBACION
void imprimir_mano_jugadores_no_comp(t_jugadores j){
	int i, k;
	
	imprimir_nombre(j.jugador[0]);
	printf("\n");
	imprimir_mano(j.jugador[0].mano);
	printf("\n");
	for(i=1;i<j.num_jugadores;i++){
		imprimir_nombre(j.jugador[i]);
		printf("\n");
		for(k=0;k<j.jugador[i].mano.num_cartas;k++){
			imprimir_mazo_no_comp (j.jugador[i].mano);
			if(j.jugador[i].mano.num_cartas==1){
				printf("|");
				mostrar_uno(j.jugador[i].mano);
			}
		}
		if(j.jugador[i].mano.num_cartas>0 && j.jugador[i].mano.num_cartas != 1){
			printf("|");
		}
		printf("\n");
	}
}

//esta funcion IMPRIME por PANTALLA la MANO de CADA JUGADOR
void imprimir_mano_jugadores(t_jugadores j){
	int i;
	for (i=0; i<j.num_jugadores; i++){
		imprimir_nombre(j.jugador[i]);
		printf("\n");
		imprimir_mano(j.jugador[i].mano);
		printf("\n");
	}
}

//esta funcion INICIALIZA el TURNO del JUGADOR
void inicializar_turno (t_jugadores *p_j){
	p_j->turno = numero_al_azar(p_j->num_jugadores);
}

//esta funcion MUESTRA por PANTALLA el TURNO del JUGADOR
void mostrar_turno_jugador (t_jugadores j){
	int turno = j.turno;
	cambiar_color_letra(RED);
	if (turno == 0)
		printf("Turno %s: ", j.jugador[turno].nombre);
	else{
		printf("Turno Robot %d: ", turno);
	}
	default_attributes();
}

/*esta funcion PASA EL TURNO 
	si el sentido es HORARIO suma 1
	si el sentido es ANTIHORARIO suma -1*/
void pasar_turno(t_jugadores *j, int sentido){
	if (sentido == ANTIHORARIO){
		j->turno = (j->turno + sentido);
		if (j->turno < 0)
			j->turno = j->num_jugadores-1;
	}
	else{
		j->turno = (j->turno + sentido)%j->num_jugadores;
	}
}

//esta funcion MUESTRA por pantalla el GANADOR DE LA PARTIDA, jugador SIN CARTAS
void mostrar_ganador(t_jugadores jugadores){
	int i, ganador;
	for (i=0; i<jugadores.num_jugadores; i++){
		if(jugadores.jugador[i].mano.num_cartas == 0){
			ganador = i;
		}
	}
	printf("===>>> HA GANADO %s. ¡FELICIDADES! <<<===\n", jugadores.jugador[ganador].nombre);
}

/*esta funcion INICIALIZA EL NOMBRE DE LOS JUGADORES, guardando cada nombre 
EN EL STRING del nombre del jugador CORRESPONDIENTE*/
void inicializar_nombre_jugadores(t_jugadores *p_jug){
	int i; 
	for (i=0; i<p_jug->num_jugadores; i++){	
		switch (i){
			case 0:
				preguntar_cadena("Tu nombre: ", p_jug->jugador[0].nombre);
				break;
			case 1:
				strcpy(p_jug->jugador[i].nombre, "Robot 1");
				break;
			case 2:
				strcpy(p_jug->jugador[i].nombre, "Robot 2");
				break;
			case 3:
				strcpy(p_jug->jugador[i].nombre, "Robot 3");
				break;
			case 4:
				strcpy(p_jug->jugador[i].nombre, "Robot 4");
				break;
			default:
				break;	
		}
	}			
}

