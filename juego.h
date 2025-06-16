#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "jugador.h"
#include "lista.h"
#include "pregunta.h"
#include "juego.h"

void menuJuego(Lista listaJugadoresTxt, Lista listaJugadoresPartida, Lista listaPreguntas,Lista listaRespuestas);

void menuModificar(Lista listaJugadoresTxt);

void infoJuego();

#endif // JUEGO_H_INCLUDED
