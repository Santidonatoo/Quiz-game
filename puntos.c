#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jugador.h"
#include "lista.h"
#include "puntos.h"
#include "pregunta.h"
#include "respuesta.h"
#include "juego.h"

PuntosPtr crearPuntosVacio(){

    PuntosPtr p = (PuntosPtr) malloc(sizeof(struct Puntos));

    p->puntuacion = 0;
    p->puntosActuales = 0;
    p->puntuacionMaxima = 0;

    return p;
};

void sumarPuntos(PuntosPtr p){

    p->puntuacion = 15;
    p->puntosActuales = p->puntosActuales + p->puntuacion;

};

void puntuacionFinalPartida(PuntosPtr p){ //Actualiza los puntos al final de la partida

    p->puntuacionMaxima = p->puntosActuales; //El chequeo de si el jugador existente supero su record esta en guardarDatosPartidaATxt

};
