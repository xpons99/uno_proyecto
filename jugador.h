#ifndef JUGADOR_H
#define JUGADOR_H

#include "mazo.h"
#include "preguntas.h"
#include "colores.h"
#define MAX_CHAR 40
#define MANO 7
#define JUGADOR 0
#define TRUE 1
#define FALSE -1
typedef struct{
	t_mazo mano;
	char nombre[MAX_CHAR];
}t_jugador;

t_mazo inicializar_mano (t_mazo *p_mano);
t_mazo calcular_jugadas_posibles(t_mazo mano, t_mazo desc);
t_carta escoger_carta (int turno, t_mazo posibles);
void mostrar_jugadas_posibles (int turno, t_mazo posibles, int comp);
void eliminar_carta_mano(t_jugador *p_jugador, t_carta tirada);
void tirar_carta (t_carta tirada);
int tiene_por_tirar(t_mazo posibles);
void anyadir_carta_mano(t_carta carta, t_mazo *p_mano);
void imprimir_mano(t_mazo mano);
void imprimir_nombre(t_jugador jug);
t_mazo calcular_jugadas_posibles_especiales(t_mazo mano, int color);
void mostrar_uno (t_mazo mano);
#endif
