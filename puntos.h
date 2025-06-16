#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

struct Puntos{

    int puntuacion; //Puntuacion durante el juego
    int puntosActuales; //Puntuacion acumulada durante el juego
    int puntuacionMaxima; //Puntuacion maxima historica en 1 juego
};

typedef struct Puntos * PuntosPtr;

PuntosPtr crearPuntosVacio();

void sumarPuntos(PuntosPtr p);

void puntuacionFinalPartida(PuntosPtr p);

#endif // PUNTOS_H_INCLUDED
