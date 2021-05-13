#ifndef TOTALJUGADORES_H
#define TOTALJUGADORES_H

#include "jugador.h"
#include "azar.h"
#include "preguntas.h"
#define MAX_JUGADORES 5
#define HORARIO 1 
#define ANTIHORARIO -1

typedef struct{
	t_jugador jugador[MAX_JUGADORES]; /*la posicion del vector es definida por el turno*/
	int num_jugadores;
	int turno;

}t_jugadores;

void inicializar_mano_jugadores(t_mazo *p_mazo, t_jugadores *p_j);
void imprimir_mano_jugadores(t_jugadores j);
void imprimir_mano_jugadores_no_comp(t_jugadores j);
void inicializar_turno(t_jugadores *p_j);
void mostrar_turno_jugador (t_jugadores j);
void pasar_turno(t_jugadores *j, int sentido);
void mostrar_ganador(t_jugadores jugadores);
void inicializar_nombre_jugadores(t_jugadores *p_jug);

#endif

