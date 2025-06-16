#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED

#include "respuesta.h"
#include "lista.h"

struct Pregunta{

    int nroPregunta;
    char pregunta[70];
    RespuestaPtr respPosibles[4];
};

typedef struct Pregunta * PreguntaPtr;

void mostrarPregunta(PreguntaPtr p);

void mostrarListaPreguntas(Lista l);

PreguntaPtr transformarTextoAPreguntas(char c[], int tam);

void cargarPreguntaDesdeTxtALista(Lista lp,Lista lr);

void relacionarPregYResp(PreguntaPtr p, Lista l);

PreguntaPtr preguntaRandom(Lista l);

//NO uso esta funcion
//int buscarRespuestaCorrectaEnPregunta(PreguntaPtr p, int tam);

#endif // PREGUNTA_H_INCLUDED
