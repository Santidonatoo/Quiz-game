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

void mostrarRespuesta(RespuestaPtr r){

    printf("%d) %s\n",r->nroRespuesta,r->respuesta);

};

void mostrarRespuestas(RespuestaPtr e[],int tam){

    for(int i = 0; i<tam; i++){
        mostrarRespuesta(e[i]);
    }
};

RespuestaPtr crearRespVacio(){ //Uso esta funcion porque trato las respuestas como un array de struct

    RespuestaPtr r = (RespuestaPtr) malloc(sizeof(struct Respuesta));

    r->nroRespuesta = -1;
    strcpy(r->respuesta,"V");
    r->nroPreguntaAsociada = -1;
    r->correcta = -1;

    return r;
};

void ordenarRespuestas(RespuestaPtr e[], int tam){ //Ordenamiento burbuja de las respuestas

    RespuestaPtr auxR = crearRespVacio(); //Creo una respuesta vacia para usarlo de auxiliar

    for(int i = 0; i<tam-1; i++){
        for(int j = i+1; j<tam; j++){
            if(e[j] > e[i]){
                auxR = e[i];
                e[i] = e[j];
                e[j] = auxR;
            }
        }
    }
};

void mostrarListaRespuestas(Lista l){

    for(int i = 0; i<obtenerTamanio(l); i++){

        RespuestaPtr r = *((RespuestaPtr*)obtenerDato(l,i));
        mostrarRespuesta(r);
    }
    printf("\n");
};

RespuestaPtr transformarTextoARespuestas(char c[], int tam){ //Idem transformarTextoAJugadores

    int pos1 = -1;
    int pos2 = -1;
    int pos3 = -1;

    char auxNumRespuesta[5] = " ";
    char auxRespuesta[20] = " ";
    char auxPregAsociada[5] = " ";
    char auxCorrecta[5] = " ";

    RespuestaPtr r = (RespuestaPtr) malloc(sizeof(struct Respuesta));

    for(int i = 0; i<tam; i++){
        if(c[i] == ';'){
            pos1 = i;
            i = tam;
        }
    }

    for(int i = pos1+1; i<tam; i++){
        if(c[i] == ';'){
            pos2 = i;
            i = tam;
        }
    }

    for(int i = pos2+1; i<tam; i++){
        if(c[i] == ';'){
            pos3 = i;
            i = tam;
        }
    }

    for(int i = 0; i<pos1; i++){
        auxNumRespuesta[i] = c[i];
    }

    for(int i = pos1+1; i<pos2; i++){
        auxRespuesta[i-pos1-1] = c[i];
    }

    for(int i = pos2+1; i<pos3; i++){
        auxPregAsociada[i-pos2-1] = c[i];
    }

    for(int i = pos3+1; i<tam; i++){
        auxCorrecta[i-pos3-1] = c[i];
    }

    r->nroRespuesta = atoi(auxNumRespuesta);
    strcpy(r->respuesta,auxRespuesta);
    r->nroPreguntaAsociada = atoi(auxPregAsociada);
    r->correcta = atoi(auxCorrecta);

    return r;
};

void cargarRespuestaDesdeTxtALista(Lista l){ //Idem cargarJugadoresDesdeTxtALista

    FILE * archivo = fopen("respuestas.txt","r");

    if(archivo == NULL){
        printf("Error al abrir el archivo!!!\n");
        exit(1);
    }

    while(!feof(archivo)){
        char aux[25] = " ";
        fgets(aux, 25, archivo);

        int tam = strlen(aux);

        RespuestaPtr r = transformarTextoARespuestas(aux,tam);

        insertarFinal(l,&r);
    }
    fclose(archivo);
};

void randomizarRespuestas(RespuestaPtr e[], int tam){ //Randomizo las respuestas para que no se muestren en el mismo orden

    for(int i = 0; i<tam; i++){
        e[i]->nroRespuesta = rand()%100; //Le asigno a cada respuesta un numero random
    }
    ordenarRespuestas(e,tam); //Las ordeno

    for(int i = 0; i<tam; i++){
        e[i]->nroRespuesta = i+1; //Le asigno de nuevo un numero de respuesta entre el 1 y el 4 usando el iterador + 1
    }
};

int buscarRespuestaCorrecta(RespuestaPtr e[], int tam){

    int posCorrecta = -1;
    int busco = 1;

    for(int i = 0; i<tam; i++){
        if(e[i]->correcta == busco){ //Si la respuesta tiene el codigo de respuesta correcta = 1, lo guardo como la correcta
            posCorrecta = e[i]->nroRespuesta;
        }
    }
    return posCorrecta; //Retorno la posicion correcta de la respuesta
};
