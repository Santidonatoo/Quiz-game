#ifndef RESPUESTA_H_INCLUDED
#define RESPUESTA_H_INCLUDED

#include "lista.h"

struct Respuesta{

    int nroRespuesta;
    char respuesta[50];
    int nroPreguntaAsociada;
    int correcta; //0 o 1
};

typedef struct Respuesta * RespuestaPtr;

void mostrarRespuesta(RespuestaPtr r);

void mostrarRespuestas(RespuestaPtr e[],int tam);

RespuestaPtr crearRespVacio();

void ordenarRespuestas(RespuestaPtr e[], int tam);

void mostrarListaRespuestas(Lista l);

RespuestaPtr transformarTextoARespuestas(char c[], int tam);

void cargarRespuestaDesdeTxtALista(Lista l);

void randomizarRespuestas(RespuestaPtr e[], int tam);

int buscarRespuestaCorrecta(RespuestaPtr e[], int tam);

#endif // RESPUESTA_H_INCLUDED
