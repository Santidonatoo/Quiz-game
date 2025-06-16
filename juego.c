#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jugador.h"
#include "lista.h"
#include "pregunta.h"
#include "juego.h"


void menuJuego(Lista listaJugadoresTxt, Lista listaJugadoresPartida, Lista listaPreguntas,Lista listaRespuestas){

    int opcion;
    char menu[10];

    cargarJugadoresDeTxtALista(listaJugadoresTxt);
    cargarRespuestaDesdeTxtALista(listaRespuestas);
    cargarPreguntaDesdeTxtALista(listaPreguntas,listaRespuestas);

    do{
        printf("\n- - - - BIENVENIDO! - - - -\n");
        printf("\n1) Jugar\n");
        printf("\n2) Mostrar Top Global de Puntos\n");
        printf("\n3) Buscar su usuario\n");
        printf("\n4) De que se trata el juego?\n");
        printf("\n5) Salir Del Juego\n");
        printf("\n- - - - - - - - - - - - - - -\n");
        printf("\nOPCION:");
        scanf("%d", &opcion);
        system("cls");

        switch (opcion){
        case 1: crearJugadoresPorTeclado(listaJugadoresPartida, listaJugadoresTxt);
        jugadoresJuegan(listaPreguntas, listaJugadoresPartida);
        guardarDatosPartidaATxt(listaJugadoresTxt,listaJugadoresPartida);
            break;
        case 2: mostrarListaJugadorTxt(listaJugadoresTxt);
            break;
        case 3: menuModificar(listaJugadoresTxt);
            break;
        case 4: infoJuego();
            break;
        case 5:
            break;
        default: printf("Error! La opcion que intentas ingresar no existe...");
            break;
        }
        if(opcion!= 5){
            printf("\n\nINGRESE UN NUMERO PARA VOLVER AL MENU\n");
            fflush(stdin);
            gets(menu);
            system("cls");
        }

    }while(opcion != 5);

};

void menuModificar(Lista listaJugadoresTxt){

    int opcion;
    char menu[10];

    int dniBusco;
    printf("\nIngrese el Dni de su usuario: \n");
    scanf("%d",&dniBusco);
    system("cls");

    int pos = buscarJugadorPorDni(listaJugadoresTxt, dniBusco);

    if(pos != -1){

        do{
            printf("\n- - - - - - - - - - - - - - -\n");
            printf("\nDesea modificar algun aspecto de su usuario?\n\n");
            printf("\n1) Modificar Alias\n");
            printf("\n2) Modificar Dni\n");
            printf("\n3) Eliminar Usuario\n");
            printf("\n4) No quiero modificar nada\n");
            printf("\n- - - - - - - - - - - - - - -\n");
            printf("\nOPCION:");
            scanf("%d", &opcion);
            system("cls");

            switch (opcion){
            case 1: modificarAlias(listaJugadoresTxt,pos);
            guardarJugadoresATxt(listaJugadoresTxt);
                break;
            case 2: modificarDni(listaJugadoresTxt,pos);
            guardarJugadoresATxt(listaJugadoresTxt);
                break;
            case 3: eliminarJugador(listaJugadoresTxt,pos);
            guardarJugadoresATxt(listaJugadoresTxt);
                break;
            case 4:
                break;
            default: printf("Error! La opcion que intentas ingresar no existe...");
                break;
            }
            if(opcion != 4){
                printf("INGRESE UN NUMERO PARA VOLVER AL MENU\n");
                fflush(stdin);
                gets(menu);
                system("cls");
            }
        }while(opcion != 4);
    }else{
        printf("\nNo se encontro el usuario seleccionado...\n");
    }
};

void infoJuego(){

    int opcion;
    char menu[10];

    do{
        printf("\n- - - - - - - - - - - - - - -\n");
        printf("\nQue desea saber acerca el Juego?\n");
        printf("\n1) De que se tratan las preguntas?\n");
        printf("\n2) Como funciona el sistema de puntuacion?\n");
        printf("\n3) Que pasa en caso de empate de puntos?\n");
        printf("\n4) De a cuantos jugadores se puede jugar?\n");
        printf("\n5) Quien es el creador del juego?\n");
        printf("\n6) Volver al menu principal\n");
        printf("\n- - - - - - - - - - - - - - -\n");
        printf("\nOPCION:");
        scanf("%d",&opcion);
        system("cls");

        switch (opcion){
            case 1: printf("\nLas preguntas no tienen una tematica exacta, son de cultura general, futbol, matematicas, etc\n\n");
                break;
            case 2: printf("\nCada pregunta respondida correctamente suma 15 puntos, si se responde incorrectamente, empieza a responder el siguiente jugador\n\n");
                break;
            case 3: printf("\nEn caso de empate, los jugadores que quedaron empatados responderan una pregunta matematica aleatoria\n\n");
            printf("El jugador que tenga la menor diferencia con el resultado, ganara un punto y se hara el desempate\n\n");
                break;
            case 4: printf("\nSe puede jugar de 2 a 4 jugadores simultaneamente\n\n");
                break;
            case 5: printf("\nEl creador del juego es el alumno de Licenciatura en Sistemas de la UNLa, Santino Donato :)\n\n");
                break;
            case 6:
            default:
                break;
            }
            if(opcion!= 6){
                printf("INGRESE UN NUMERO PARA VOLVER AL MENU\n");
                fflush(stdin);
                gets(menu);
                system("cls");
            }

    }while(opcion != 6);
};
