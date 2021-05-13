#ifndef MAZO_H
#define MAZO_H

#include "carta.h"

#define MAX 108
#define CARTAS_CON_COLOR 100
#define SALTO_LINEA 20


typedef struct
{
	t_carta v[MAX];
	int num_cartas;

}t_mazo;

void inicializar_mazo(t_mazo *p_mazo);
void inicializar_mazo_desordenado (t_mazo *p_mazo);
t_carta robar_carta(t_mazo *p_mazo);
void inicializar_mazo_descartes(t_mazo *p_mazo, t_mazo *p_descartes);
void mezclar_mazo(t_mazo *p_mazo);
void imprimir_mazo(t_mazo mazo);
void imprimir_mazo_desc(t_mazo mazo);	
void anyadir_carta(t_mazo *p_mazo, t_carta carta);
void imprimir_mazo_no_comp(t_mazo mazo);
void actualizar_mazo_desc(t_carta tirada,t_mazo *p_descartes);
void rellenar_mazo (t_mazo *mazo, t_mazo *descartes);

#endif
