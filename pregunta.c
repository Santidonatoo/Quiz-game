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

#define TAM 4

void mostrarPregunta(PreguntaPtr p){

    printf("\n%s\n",p->pregunta);
    mostrarRespuestas(p->respPosibles,TAM);
    printf("\n");
};

void mostrarListaPreguntas(Lista l){

    for(int i = 0; i<obtenerTamanio(l); i++){

        PreguntaPtr p = *((PreguntaPtr*)obtenerDato(l,i));
        mostrarPregunta(p);
    }
    printf("\n");
};

PreguntaPtr transformarTextoAPreguntas(char c[], int tam){ //Idem transformarTextoAJugadores

    int pos1 = -1;

    char auxNumPregunta[3] = " ";
    char auxPregunta[65] = " ";

    PreguntaPtr p = (PreguntaPtr) malloc(sizeof(struct Pregunta));

    for(int i = 0; i<tam; i++){
        if(c[i] == ';'){
            pos1 = i;
            i = tam;
        }
    }

    for(int i = 0; i<pos1; i++){
        auxNumPregunta[i] = c[i];
    }

    for(int i = pos1+1; i<tam; i++){
        auxPregunta[i-pos1-1] = c[i];
    }

    p->nroPregunta = atoi(auxNumPregunta);
    strcpy(p->pregunta,auxPregunta);

    return p;
};

void cargarPreguntaDesdeTxtALista(Lista lp, Lista lr){ //Idem cargarJugadoresDesdeTxtALista

    FILE * archivo = fopen("preguntas.txt","r");

    if(archivo == NULL){
        printf("Error al abrir el archivo!!!\n");
        exit(1);
    }

    while(!feof(archivo)){
        char aux[70] = " ";
        fgets(aux, 70, archivo);

        PreguntaPtr p = transformarTextoAPreguntas(aux,70);

        relacionarPregYResp(p,lr); //Relaciono las preguntas y las respuestas con su numero

        insertarFinal(lp,&p); //Inserto preguntas y respuestas en la lista preguntas
    }
    fclose(archivo);
};

void relacionarPregYResp(PreguntaPtr p, Lista l){

    for(int i = 0; i<obtenerTamanio(l); i++){
        RespuestaPtr r = *((RespuestaPtr*)obtenerDato(l,i));
        if(p->nroPregunta == r->nroPreguntaAsociada){ //Si el num de la pregunta es igual al numero de preg asociada en la respuesta, lo guardo en las respuestas
            p->respPosibles[r->nroRespuesta-1] = r;
        }
    }
    randomizarRespuestas(p->respPosibles,TAM); //Randomizo las respuestas de esa pregunta
};

PreguntaPtr preguntaRandom(Lista l){ //Randomizo las preguntas para que se muestren mezcladas en el juego

    int aux = rand()%obtenerTamanio(l);
    PreguntaPtr p = *((PreguntaPtr*)obtenerDato(l,aux)); //Obtengo una pregunta random

    return p; //Retorno la pregunta
};

/* NO uso esta funcion
int buscarRespuestaCorrectaEnPregunta(PreguntaPtr p, int tam){

    int posCorrecta = -1;

    do{
        posCorrecta = buscarRespuestaCorrecta(p->respPosibles,tam);
    }while(posCorrecta != 1);

    return posCorrecta;
};
*/
