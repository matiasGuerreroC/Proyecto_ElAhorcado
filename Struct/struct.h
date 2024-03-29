#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

#include "../DataStructures/List/list.h"
#include "../DataStructures/Map/Map.h"

typedef struct {
    char palabra[25];
    char pista[100];
    int nivel;
} Palabra;

typedef struct {
    char palabraSecreta[50];
    char palabraActual[50];
    char pista[50];
    int nivel;
    int puntosNivel;
    int intentosRestantes;
    List *letrasJugadas;
} Nivel;

typedef struct {
    char nombre[50];
    int puntos;
    int nivel;
    int idioma;
    int puntosSubirNivel;
    bool flagSubirNivel;
    Map *palabrasJugadas;
} Jugador;

#endif //STRUCTS_H