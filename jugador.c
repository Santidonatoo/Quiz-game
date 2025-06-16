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

void mostrarJugador(JugadorPtr j){//Este mostrar Jugador lo uso para mostrarlos adentro del Juego (extraigo del txt)

    printf("\n- - - JUGADOR - - -\n");

    printf("\nALIAS: %s | DNI: %d | MAX PUNTUACION: %d\n", j->alias, j->dni, j->puntos->puntuacionMaxima);

};

void mostrarListaJugadorTxt(Lista lista){//Esta es la funcion que uso en conjunto a la primera, funciona para mostrar el txt

    if(estaVacia(lista)==TRUE){//Chequeo si hay datos en la lista o si esta vacia
        printf("No hay datos previos de ningun jugador...\n");
    }else{
        for ( int i = 0; i < obtenerTamanio(lista); ++i){//Si hay datos, muestro los jugadores
            JugadorPtr j = *((JugadorPtr*) obtenerDato(lista, i));
            if(j->dni != 0){//Validacion para confirmar que no se este cargando ningun jugador vacio
                mostrarJugador(j);
            }
        }
        printf("\n");
    }
};

void mostrarJugadorPartida(JugadorPtr j){//Esta es la funcion que uso para mostrar a los jugadores al final de la partida

    printf("\n- - - JUGADOR - - -\n");

    printf("\nALIAS: %s | DNI: %d | PUNTUACION FINAL: %d\n", j->alias, j->dni, j->puntos->puntosActuales);

};

void mostrarListaJugadorPartida(Lista listaPartida){

    for ( int i = 0; i < obtenerTamanio(listaPartida); ++i){

        JugadorPtr j = *((JugadorPtr*) obtenerDato(listaPartida, i));
        if(j->dni != -1){//Chequeo que no me haya ingresado ningun dni invalido
            mostrarJugadorPartida(j);
        }
    }
    printf("\n");
};


JugadorPtr crearJugadorPorTeclado(Lista l){//Funcion que me sirve para ingresar a los jugadores nuevos o existentes que vayan a jugar

    JugadorPtr j = (JugadorPtr) malloc(sizeof(struct Jugador));

    //printf("\nCreando Jugador...\n");

    printf("Ingrese su dni:\n");
    scanf("%d", &j->dni);

    int auxDni = buscarJugadorPorDni(l,j->dni);
    if(auxDni == -1){ //Osea que no se encontro registro previo del jugador
        char aux[20] = " ";
        printf("Ingrese su alias:\n");
        fflush(stdin);
        gets(aux);
        strcpy(j->alias,aux);
    }else{ //Se encontro al jugador
        JugadorPtr p = *((JugadorPtr*)obtenerDato(l,auxDni));
        printf("Ya jugaste una vez al juego, tu alias es: %s (Se puede cambiar desde el menu principal)\n",p->alias);
        strcpy(j->alias,p->alias);//Copio el nombre que ya tenia anteriormente, Si lo quiere cambiar lo puede hacer desde el menu
    }
    j->puntos = crearPuntosVacio();//Creo los puntos vacios (todos en 0)

    return j;
};

void crearJugadoresPorTeclado(Lista listaP, Lista listaTxt){//listaP = lista de la partida(lista local)

    int t;
    printf("\nIngrese la cantidad de jugadores que van a jugar(2 a 4 Jugadores!)\n");
    scanf("%d",&t);

    while(t>4 || t<=1){//Chequeo que no me ingresen algun valor incorrecto
        printf("\nERROR, cantidad de jugadores invalida, vuelva a intentar...\n");
        printf("\nIngrese la cantidad de jugadores que van a jugar(2 a 4 Jugadores!)\n");
        scanf("%d",&t);
    }

    system("cls");//Borro la consola para que no se acumule el texto innecesario en la pantalla

    for(int i = 0; i<t; i++){//Uso la funcion de crearPorTeclado y lo inserto en la lista de la partida
        printf("\nCreando Jugador %d\n",i+1);
        JugadorPtr j = crearJugadorPorTeclado(listaTxt);
        insertarFinal(listaP,&j);
    }
};

JugadorPtr transformarTextoAJugadores(char c[], int tam){
    //Esta funcion lo que hace es tomar la linea completa del txt y lo separa en variables, usando los delimitadores (;)

    int pos1 = -1; //Auxiliares para tomar las posiciones de mis delimitadores (;)
    int pos2 = -1;

    char auxAlias[30] = " ";
    char auxDNI[30] = " "; //Auxiliares para las varibales que voy a tomar del txt
    char auxPuntos[30] = " ";

    JugadorPtr j = (JugadorPtr) malloc(sizeof(struct Jugador)); //Creo un JugadorPtr para guardar los datos, luego lo retorno
    PuntosPtr aux = (PuntosPtr) malloc(sizeof(struct Puntos));

    for(int i = 0; i<tam; i++){//Tomo la pos del primer delimitador
        if(c[i] == ';'){
            pos1 = i;
            i = tam;
        }
    }

    for(int i = pos1+1; i<tam; i++){//Tomo la pos del segundo delimitador
        if(c[i] == ';'){
            pos2 = i;
            i = tam;
        }
    }

    for(int i = 0; i<pos1; i++){//Hasta el primer delimitador, guardo el nombre en un auxiliar
        auxAlias[i] = c[i];
    }

    for(int i = pos1+1; i<pos2; i++){//Desde el primer delimitador al segundo, guardo el dni en un auxiliar
        auxDNI[i-pos1-1] = c[i];
    }

    for(int i = pos2+1; i<tam; i++){//Desde el segundo delimitador, hasta el final de la linea, guardo los puntos en un auxiliar
        auxPuntos[i-pos2-1] = c[i];
    }

    strcpy(j->alias,auxAlias); //Copio el auxiliar del alias que tome y lo guardo en el JugadorPtr J que cree
    j->dni = atoi(auxDNI); //Transformo mi auxDNI(Char) en int y lo guardo en j->dni
    aux->puntuacionMaxima = atoi(auxPuntos);
    j->puntos = aux;

    return j;
};

void cargarJugadoresDeTxtALista(Lista lista){//Uso esta funcion para tomar lo que hay en el txt y guardarlo en la lista

    FILE * archivo = fopen("jugadores.txt", "r");

    if(archivo == NULL){//Validacion de archivo de texto existento o no
        printf("Error al abrir el archivo!!!\n");
        exit(1);
    }

    while(!feof(archivo)){
        char aux[40] = " ";
        fgets(aux, 40, archivo); //Tomo la linea completa y la guardo en una variable vacia

        JugadorPtr j = transformarTextoAJugadores(aux,40); //Transformo esa linea completa en una struct
        if(j->dni != 0){
            insertarInicio(lista, &j);//Guardo los datos en la listaTxt
        }
    }
    fclose(archivo);
};

void guardarJugadoresATxt(Lista lista){ //Funcion para guardar los datos en el txt y que quede consistencia de los datos

    FILE * archivo = fopen("jugadores.txt","w");
    int aux = 1;

    for(int i = 0; i<obtenerTamanio(lista); i++){
        if(aux == 0){
            fprintf(archivo,"\n");//Espacio para todas las lineas menos la primera
        }
        JugadorPtr j = *((JugadorPtr*)obtenerDato(lista,i));
        fprintf(archivo,"%s;%d;%d",j->alias,j->dni,j->puntos->puntuacionMaxima); //Lo guardo con el formato previo que ya tengo
        aux = 0;
    }
    fclose(archivo);
};

int buscarJugadorPorDni(Lista l, int busco){//Funcion que me va a servir luego para el ABM

    int pos = -1;

    for(int i = 0; i<obtenerTamanio(l); i++){
        JugadorPtr j = *((JugadorPtr*)obtenerDato(l,i));
        if(j->dni == busco){
            pos = i;
        }
    }
    return pos;
};

int jugadorComienzaJuego(Lista listaPreg){ //Funcion que uso para el juego

    PreguntaPtr p = preguntaRandom(listaPreg); //Muestro pregunta random
    mostrarPregunta(p);
    int respuestaCorrecta = buscarRespuestaCorrecta(p->respPosibles,4);//Busco respuesta correcta en la pregunta

    return respuestaCorrecta; //Retorno respuesta correcta
};

void jugadoresJuegan(Lista listaPreg,Lista listaJugadoresPartida){ //Funcion principal para el juego

    for(int i = 0; i<obtenerTamanio(listaJugadoresPartida); i++){

        JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresPartida,i));

        printf("\n---Turno del jugador %d (%s)---\n",i+1,j->alias);

        int respuestaJugador = 1; //Valores para que entren al while, despues se pisan
        int respuestaCorrecta = 1;

        while(respuestaCorrecta == respuestaJugador){ //Mientras la respuesta sea correcta, sigue jugando el jugador
            respuestaCorrecta = jugadorComienzaJuego(listaPreg); //Guardo la respuesta correcta (piso el primer dato)

            printf("\nRespuesta Final: ");
            scanf("%d",&respuestaJugador); //Responde el jugador

            while(respuestaJugador<1 || respuestaJugador>4){ //Validacion de numero de opcion
                printf("\nNumero de respuesta invalida, ingrese nuevamente...\n");
                printf("\nRespuesta Final: ");
                scanf("%d",&respuestaJugador);
            }

            if(respuestaJugador == respuestaCorrecta){ //Mensaje si es correcta o incorrecta
                printf("\nCorrecto!\n");
                sumarPuntos(j->puntos);//Sumo 15 puntos por pregunta
            }else{
                printf("\nIncorrecto :(\n");
            }
        }
    }
    system("cls");
    printf("\nFIN DEL JUEGO\n");
    mostrarListaJugadorPartida(listaJugadoresPartida); //Muestro la lista final
    buscarGanador(listaJugadoresPartida); //Busco el ganador, si hay empate, hace desempate
};

void buscarGanador(Lista listaJugadoresPartida){

    int max = -1;
    char ganador[25] = " ";

    int chequeoEmpate;
    int posDelGanador;

    for(int i = 0; i<obtenerTamanio(listaJugadoresPartida); i++){//Busqueda del ganador
        JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresPartida,i));
        if(i == 0){
            max = j->puntos->puntosActuales;
            strcpy(ganador, j->alias);
            posDelGanador = i;
        }
        if(max < j->puntos->puntosActuales){
            max = j->puntos->puntosActuales;
            strcpy(ganador, j->alias);
            posDelGanador = i;
        }
    }

    chequeoEmpate = empate(listaJugadoresPartida,max); //1 = Empate | 2 = No empate
    if(chequeoEmpate == 1){ //Mensaje de empate
        system("cls");
        printf("\nHay Empate!!\n");
    }
    while(chequeoEmpate == 1){ //Se hace el desempate
        posDelGanador = desempate(listaJugadoresPartida,max);
        chequeoEmpate = empate(listaJugadoresPartida,max);
    }

    JugadorPtr jugadorGanador = *((JugadorPtr*)obtenerDato(listaJugadoresPartida,posDelGanador));
    printf("\nEl ganador es: %s, Felicidades!!\n",jugadorGanador->alias);
};

int empate(Lista listaJugadoresPartida,int maximo){ //Funcion que chequea si hay empate o no

    int chequeoMax = 0;

    for(int i = 0; i<obtenerTamanio(listaJugadoresPartida); i++){
        JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresPartida,i));
        if(maximo == j->puntos->puntosActuales){//chequeo los demas maximos en base del primer maximo guardado, acumulo si encuentro
            chequeoMax++;
        }
    }

    int hayEmpate;

    if(chequeoMax>=2){//si en el chequeo se encontraron 2 o mas maximos iguales se retorna un 1 = empate
        hayEmpate = 1;
    }
    if(chequeoMax<=1){//si en el chequeo se encontro 1 o menos maximos iguales, se retorna un 0 = no empate
        hayEmpate = 0;
    }
    return hayEmpate;
};

int preguntaDesempate(){ //Si hay empate se activa esta funcion, muestra la pregunta y retorna el resultado

    int a,b,c;

    a = rand()%151;
    b = rand()%151;
    c = rand()%91;

    int resultado = a+(b*c);

    printf("\n%d + %d * %d\n",a,b,c);

    return resultado;
};

int desempate(Lista listaJugadoresPartida, int maximo){

    int respuestaCorrecta = preguntaDesempate();//Muestra la pregunta de desempate
    int respuestaJugador;
    int resto;
    int menorRes;
    int posJugadorGanador;

    for(int i = 0; i<obtenerTamanio(listaJugadoresPartida); i++){
        JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresPartida,i));

        if(maximo == j->puntos->puntosActuales){//Solo pueden contestar los empatados
            printf("\nResponde el jugador %d (%s)\n",i+1,j->alias);
            printf("\nRespuesta Final: ");
            scanf("%d",&respuestaJugador);
        }

        if(respuestaJugador>respuestaCorrecta){//Lo hago para que no me quede negativo
            resto = respuestaJugador - respuestaCorrecta;
        }
        if(respuestaCorrecta>respuestaJugador){//Lo hago para que no me quede negativo
            resto = respuestaCorrecta - respuestaJugador;
        }
        if(i == 0){//Guardo la primer diferencia como la menor
            menorRes = resto;
            posJugadorGanador = i;
        }
        if(resto<menorRes){//Chequeo si hay otra diferencia mas chica que la primera y cambio en caso de que si
            menorRes = resto;
            posJugadorGanador = i;
        }
    }

    printf("\nEl resultado es: %d\n",respuestaCorrecta);

    JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresPartida, posJugadorGanador));
    j->puntos->puntosActuales = j->puntos->puntosActuales + 1; //Suma un punto al jugador que mas se aproximo a la respuesta

    return posJugadorGanador; //Devuelvo la pos del ganador para tomar el dato de esa posicion en buscarGanador
};

void guardarDatosPartidaATxt(Lista listaJugadoresTxt, Lista listaJugadoresPartida){
    //Funcion que actualiza los datos del archivo de texto

    for(int i = 0; i<obtenerTamanio(listaJugadoresPartida); i++){
        JugadorPtr jugadorPartida = *((JugadorPtr*)obtenerDato(listaJugadoresPartida,i));
        int pos = buscarJugadorPorDni(listaJugadoresTxt, jugadorPartida->dni);

        if(pos != -1){ //El jugador existe en la lista historica
            JugadorPtr jugadorTxt = *((JugadorPtr*)obtenerDato(listaJugadoresTxt,pos));
            if(jugadorPartida->puntos->puntosActuales > jugadorTxt->puntos->puntuacionMaxima){
                //Si el jugador supero su highscore previamente guardado, lo cambio por su nuevo record
                jugadorTxt->puntos->puntuacionMaxima = jugadorPartida->puntos->puntosActuales;
            }
        }else{ //El jugador no existe en la lista historica
            puntuacionFinalPartida(jugadorPartida->puntos);
            insertarFinal(listaJugadoresTxt, &jugadorPartida);
        }
    }
    guardarJugadoresATxt(listaJugadoresTxt); //Uso la funcion para guardar los datos en el txt
    liberarlista(listaJugadoresPartida); //Libero la lista de la partida para poder volver a jugar y que no haya datos guardados
};

void modificarAlias(Lista listaJugadoresTxt, int pos){ //abM

    char nuevoAlias[20];

    JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresTxt,pos));

    printf("\nIngrese el nuevo Alias: \n");
    fflush(stdin);
    gets(nuevoAlias);
    strcpy(j->alias,nuevoAlias);

};

void modificarDni(Lista listaJugadoresTxt, int pos){ //abM

    int nuevoDni = 0;

    JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresTxt,pos));

    printf("\nIngrese el nuevo Dni: \n");
    scanf("%d",&nuevoDni);
    j->dni = nuevoDni;

};

void eliminarJugador(Lista listaJugadoresTxt, int pos){ //aBm

    int decision;
    JugadorPtr j = *((JugadorPtr*)obtenerDato(listaJugadoresTxt,pos));

    printf("\nEsta seguro que desea eliminar el usuario '%s'?\n",j->alias);
    printf("1) Si, estoy seguro.\n");
    printf("2) No, me arrepenti.\n");
    scanf("%d",&decision);

    if(decision == 1){
        remover(listaJugadoresTxt,pos,&j);
    }
};
