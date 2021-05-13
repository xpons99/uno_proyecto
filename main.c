#include <stdio.h>
#include "colores.h"
#include "azar.h"
#include "preguntas.h"
#include "carta.h"
#include "mazo.h"
#include "jugador.h"
#include "totaljugadores.h"
#include "partida.h"


int main(){
	t_partida p;

	inicializar_partida(&p);
	inicializar_jugadores(&p);
	mostrar_estado(p);
	do{

		realizar_jugada(&p);
		esperar();
		if(p.jugadores.jugador[p.jugadores.turno].mano.num_cartas!=0){
			pasar_turno(&p.jugadores, p.sentido);
		}
		mostrar_estado(p);
	}while(mirar_fin_partida(p.jugadores.jugador[p.jugadores.turno].mano.num_cartas));
	printf("===>>> FIN PARTIDA <<<===\n");
	mostrar_estado(p);
	mostrar_ganador(p.jugadores);
	esperar();
}
