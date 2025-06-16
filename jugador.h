#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "pregunta.h"
#include "puntos.h"
#include "lista.h"

struct Jugador{

    char alias[20];
    int dni;
    PuntosPtr puntos;
};

typedef struct Jugador * JugadorPtr;

void mostrarJugador(JugadorPtr j);

void mostrarJugadorPartida(JugadorPtr j);

void mostrarListaJugadorTxt(Lista lista);

void mostrarListaJugadorPartida(Lista listaPartida);

JugadorPtr crearJugadorPorTeclado(Lista l);

void crearJugadoresPorTeclado(Lista listaP, Lista listaTxt);

JugadorPtr transformarTextoAJugadores(char c[], int tam);

void cargarJugadoresDeTxtALista(Lista lista);

void guardarJugadoresATxt(Lista lista);

int buscarJugadorPorDni(Lista l, int busco);

int jugadorComienzaJuego(Lista listaPreg);

void jugadoresJuegan(Lista listaPreg,Lista listaJugadoresPartida);

void buscarGanador(Lista listaJugadoresPartida);

int empate(Lista listaJugadoresPartida, int maximo);

int preguntaDesempate();

int desempate(Lista listaJugadoresPartida,int maximo);

int dobleEmpate(Lista listaJugadoresPartida, int maximo);

void guardarDatosPartidaATxt(Lista listaJugadoresTxt, Lista listaJugadoresPartida);

void modificarAlias(Lista listaJugadoresTxt, int pos);
void modificarDni(Lista listaJugadoresTxt, int pos); //ABM completo para jugadores
void eliminarJugador(Lista listaJugadoresTxt, int pos);

#endif // JUGADOR_H_INCLUDED
