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

int main()
{
    srand(time(NULL));

    Lista listaJugadoresTxt = crearLista(sizeof(JugadorPtr));
    Lista listaJugadoresP = crearLista(sizeof(JugadorPtr));
    Lista listaPreguntas = crearLista(sizeof(PreguntaPtr));
    Lista listaRespuestas = crearLista(sizeof(RespuestaPtr));

    menuJuego(listaJugadoresTxt,listaJugadoresP,listaPreguntas,listaRespuestas);

    return 0;
}
