#ifndef PARTIDA_H
#define PARTIDA_H

#include "totaljugadores.h"
#include "mazo.h"
#include "jugador.h"
#include "preguntas.h"
#include "azar.h"

#define MAX_L 200
#define MIN_JUG 3
#define MAX_JUG 5
#define FALSE -1
#define TRUE 1
#define HORARIO 1
#define ANTIHORARIO -1
#define ROBA_DOS 2
#define ROBA_CUATRO 4

typedef struct{

	int fin_partida;
	int modo_comprobacion;
	int sentido;
	int color_seleccionado;
	t_mazo mazo;
	t_mazo descartes;
	t_jugadores jugadores;
}t_partida;

void inicializar_partida (t_partida *p_p);
void inicializar_jugadores (t_partida *p_p);
void mostrar_estado(t_partida p);
void realizar_jugada(t_partida *p_p);
void mostrar_sentido(int sentido);
void inicializar_sentido(t_partida *p_p);
void actualizar_sentido(t_partida *p_p);
void cambiar_color(t_partida *p_p, int turno);
void mostrar_color_elegido(int color);
void operar_especiales (t_carta tirada, t_partida *p_p, int turno);
int mirar_fin_partida (int num_cartas);
void robar_cartas_draw (t_partida *p_p, int num, int turno);

#endif
