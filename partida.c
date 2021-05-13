#include <stdio.h>
#include "partida.h"

//Inicializa todo lo que se refiere con la partida
void inicializar_partida (t_partida *p_p){

	inicializar_azar();
	inicializar_mazo(&p_p->mazo);
	inicializar_mazo_descartes(&p_p->mazo, &p_p->descartes);
	inicializar_mazo_desordenado (&p_p->mazo);
	inicializar_sentido(p_p);
	p_p->fin_partida=FALSE;
}

//Inicializa los JUGADORES ademas del modo de comprobacion
void inicializar_jugadores(t_partida *p_p){
	p_p->jugadores.num_jugadores = preguntar_n_en_rango("Numero de jugadores", MIN_JUG, MAX_JUG);
	inicializar_nombre_jugadores(&p_p->jugadores);
	p_p->modo_comprobacion = preguntar_si_o_no("Quieres ejecutar en modo comprobacion");
	inicializar_mano_jugadores(&p_p->mazo, &p_p->jugadores);
	inicializar_turno(&p_p->jugadores);
}

/*FUNCION QUE MUESTRA EL ESTADO DE LA PARTIDA (MAZO, MAZO DESCARTES, SENTIDO, NOMBRE JUGADORES, MANO Y EL TURNO )
EN ESTA FUNCION SE DIFERENCIA EL MODO DE LA PARTIDA (COMPROBACION [S/N])*/
void mostrar_estado(t_partida p){
	printf("Mazo:\n"); 
	if (p.modo_comprobacion == 0){
		imprimir_mazo_no_comp(p.mazo);
		printf("|(%d)\n", p.mazo.num_cartas);
		imprimir_mazo_desc(p.descartes);
		if (p.descartes.v[0].palo >= WILD){
			mostrar_color_elegido(p.color_seleccionado);
		}
		mostrar_sentido(p.sentido);
		imprimir_mano_jugadores_no_comp(p.jugadores);
		printf("\n");
	}
	else{
		imprimir_mazo(p.mazo);
		printf("\n");
		imprimir_mazo_desc(p.descartes);
		if (p.descartes.v[0].palo >= WILD){
			mostrar_color_elegido(p.color_seleccionado);
		}
		mostrar_sentido(p.sentido);
		imprimir_mano_jugadores(p.jugadores);
		printf("\n");
	}	
}

//FUNCION QUE REALIZA TODA LA JUGADA DE LA PARTIDA
void realizar_jugada(t_partida *p_p){
	t_mazo posibles;
	t_carta tirada, robada;
	
	mostrar_turno_jugador (p_p->jugadores);
	int turno = p_p->jugadores.turno, puede_tirar, i, siguiente, trobada=FALSE;
	
	if (p_p->descartes.v[0].palo >= WILD){ //SI LA CARTA CON LA QUE COMPARAMOS PARA TIRAR CAMBIA EL COLOR
		posibles = calcular_jugadas_posibles_especiales(p_p->jugadores.jugador[turno].mano, p_p->color_seleccionado);
		trobada = TRUE;
	}
	else{ 								  //SI LA CARTA CON LA QUE COMPARAMOS NO ES UNA QUE CAMBIA COLOR
		posibles = calcular_jugadas_posibles(p_p->jugadores.jugador[turno].mano, p_p->descartes);
	}
	puede_tirar = tiene_por_tirar(posibles); //MIRA SI TIENE POR TIRAR
	if(puede_tirar==FALSE){						//NO PUEDE TIRAR
		robada = robar_carta(&p_p->mazo);			//ROBA CARTA
		if(p_p->mazo.num_cartas == 0){					//SI NO HAY CARTAS, RELLENA MAZO
			rellenar_mazo(&p_p->mazo, &p_p->descartes);
		}
		printf("Coje del mazo: ");
		imprimir_carta(robada);
		printf(" ");		
		if(robada.palo==p_p->descartes.v[0].palo||robada.color==p_p->descartes.v[0].color || robada.palo >= WILD || robada.color == p_p->color_seleccionado){	
														//PUEDE TIRAR ROBADA
			tirar_carta(robada);
			tirada = robada;
			actualizar_mazo_desc(robada,&p_p->descartes);
		}
		else{											//NO PUEDE TIRAR ROBADA
			printf("Ha pasado");
			anyadir_carta_mano(robada, &p_p->jugadores.jugador[turno].mano);	
		}
	}else{										//SI PUEDE TIRAR SIN ROBAR
		mostrar_jugadas_posibles (turno, posibles, p_p->modo_comprobacion);
		tirada = escoger_carta (turno, posibles);
		tirar_carta(tirada);
		eliminar_carta_mano(&p_p->jugadores.jugador[turno], tirada);
		actualizar_mazo_desc(tirada,&p_p->descartes);
	}
	operar_especiales (tirada, p_p, turno);		//SI LA CARTA TIRADA ES UNA DE LAS ESPECIALES, OPERAN DISTINTO
	
	/*if (trobada == TRUE){
		p_p->color_seleccionado=WHITE;
	}*/
}

//Se inicializa el sentido HORARIO de la partida
void inicializar_sentido(t_partida *p_p){
	p_p->sentido = HORARIO;
}

//Muestra al lado del mazo DESCARTES el SENTIDO de la partida
void mostrar_sentido(int sentido){
	printf(" Sentido: ");
	cambiar_color_letra(BLUE);
	if(sentido == HORARIO){
		printf("HORARIO\n");
	}
	else{
		printf("ANTIHORARIO\n");
	}
	default_attributes();
}

//Actualiza el sentido, se ejecuta unicamente cuando han tirado la carta REVERSE
void actualizar_sentido(t_partida *p_p){
	if (p_p->sentido == HORARIO){
		p_p->sentido = ANTIHORARIO;
	}	
	else{ 
		p_p->sentido = HORARIO;
	}
}

//Cambia el color en juego al tirar una de las cartas que cambian el color, para pasar a jugar con este color
void cambiar_color(t_partida *p_p, int turno){
	if(turno != 0){
		p_p->color_seleccionado = numero_al_azar(4)+1;
	}
	else{
		p_p->color_seleccionado = preguntar_color();
	}
}

//Muestra el color elegido en el cambio de color
void mostrar_color_elegido(int color){
	printf("Color escogido: |");
	cambiar_color_fondo(color);
	printf("   ");
	default_attributes();
	printf("|");
}

//Realiza las operaciones correspondientes al tirar una carta especial (+2, R, S, W, W+4)	
void operar_especiales (t_carta tirada, t_partida *p_p, int turno){
	switch(tirada.palo){
			case DRAW_2:
				robar_cartas_draw (p_p, ROBA_DOS, turno);
				pasar_turno(&p_p->jugadores, p_p->sentido);
				break;
			case REVERSE:
				pasar_turno(&p_p->jugadores, p_p->sentido);
				actualizar_sentido(p_p);
			case SKIP:
				pasar_turno(&p_p->jugadores, p_p->sentido);
				break;
			case WILD:
				cambiar_color(p_p, turno);
				mostrar_color_elegido(p_p->color_seleccionado);
				break;
			case WILD_DRAW:
				cambiar_color(p_p, turno);
				mostrar_color_elegido(p_p->color_seleccionado);
				robar_cartas_draw (p_p, ROBA_CUATRO, turno);
				pasar_turno(&p_p->jugadores, p_p->sentido);
				break;
		}
}

//Comprueba si es el fin de partida
int mirar_fin_partida (int num_cartas){
	if (num_cartas != 0){
		return TRUE;
	}else {
		return 0;
	}
}

//Roba cartas al tirar una carta que hacen robar cartas
void robar_cartas_draw (t_partida *p_p, int num, int turno){
	int i, siguiente = turno+p_p->sentido;
	
	if (p_p->sentido == ANTIHORARIO && turno == 0){
		siguiente = p_p->jugadores.num_jugadores-1;
	}	
	else if (p_p->sentido == HORARIO && turno == p_p->jugadores.num_jugadores-1){
		siguiente = 0;
	}
	for (i=0; i<num; i++){
		anyadir_carta_mano(robar_carta(&p_p->mazo), &p_p->jugadores.jugador[siguiente].mano);
	}
}
