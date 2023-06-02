#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>

//====================================================================================================
// Importar header de backend
//====================================================================================================

#include "backend.h"

//====================================================================================================
// Importar librerias de las estructuras de datos
//====================================================================================================
#include "../DataStructures/ArrayList/arraylist.h"
#include "../DataStructures/List/list.h"
#include "../DataStructures/Map/Map.h"
#include "../FrontEnd/frontend.h"

//====================================================================================================
// Importar structs, funciones de frontend y backend
//====================================================================================================
#include "../Struct/struct.h"

//====================================================================================================
// Funciones de backend
//====================================================================================================

// Función para quitar los tildes de una cadena
char* quitar_tildes(char* cadena)
{
    const char *originales = "áéíóúÁÉÍÓÚ"; // cadena de caracteres con tildes
    const char *reemplazos = "aeiouAEIOU"; // cadena de caracteres sin tildes
    char* nueva_cadena = (char*) malloc(strlen(cadena) + 1); // se reserva memoria para la nueva cadena

    if (nueva_cadena == NULL) // si no se pudo reservar memoria, se retorna NULL
    {
        return NULL;
    }

    int j = 0; // indice para la nueva cadena

    for(int i = 0; cadena[i] != '\0'; i++) // se recorre la cadena original
    {   
        // booleanos para saber si el caracter actual tiene tilde y si ya se reemplazó
        bool conTilde = false;
        bool flag = false;

        // se recorre la cadena de caracteres con tildes
        for(int k = 0; originales[k] != '\0'; k++)
        {
            if(cadena[i] == originales[k]) // si el caracter actual tiene tilde
            {
                if(!flag) // si no se ha reemplazado
                {
                    i++;
                }
                else // si ya se reemplazó
                {
                    conTilde = true; // se marca que el caracter actual tiene tilde
                    nueva_cadena[j++] = reemplazos[k/2]; // se agrega el caracter sin tilde a la nueva cadena
                    break; // se sale del ciclo
                }

                flag = true; // se marca que ya se reemplazó
            }
        }

        if(!conTilde) // si el caracter actual no tiene tilde
        {   
            // se agrega el caracter a la nueva cadena
            nueva_cadena[j++] = cadena[i];
        }
    }

    nueva_cadena[j] = '\0'; // se agrega el caracter nulo al final de la nueva cadena
    return nueva_cadena; // se retorna la nueva cadena
}

// Función para buscar una palabra aleatoria
void agregarPalabraAleatoria(Jugador *jugador, Nivel *nivel)
{   
    char archivo[20];

    int totalPalabras = 100;

    // Se verifica el nivel seleccionado
    switch(jugador->nivel)
    {
        case 1:
            strcpy(archivo, "DataBase/03.txt");
            totalPalabras = 104;
            break;
        case 2:
            strcpy(archivo, "DataBase/04.txt");
            totalPalabras = 407;
            break;
        case 3:
            strcpy(archivo, "DataBase/05.txt");
            totalPalabras = 1007;
            break;
        case 4:
            strcpy(archivo, "DataBase/06.txt");
            totalPalabras = 766;
            break;
        case 5:
            strcpy(archivo, "DataBase/07.txt");
            break;
        case 6:
            strcpy(archivo, "DataBase/08.txt");
            break;
        case 7:
            strcpy(archivo, "DataBase/09.txt");
            break;
        case 8:
            strcpy(archivo, "DataBase/10.txt");
            break;
        case 9:
            strcpy(archivo, "DataBase/11.txt");
            break;
        case 10:
            strcpy(archivo, "DataBase/12.txt");
            break;
        case 11:
            strcpy(archivo, "DataBase/13.txt");
            break;
        case 12:
            strcpy(archivo, "DataBase/14.txt");
            break;
        case 13:
            strcpy(archivo, "DataBase/15.txt");
            break;
        case 14:
            strcpy(archivo, "DataBase/16.txt");
            break;
        case 15:
            strcpy(archivo, "DataBase/17.txt");
            break;
        case 16:
            strcpy(archivo, "DataBase/18.txt");
            break;
        case 17:
            strcpy(archivo, "DataBase/19.txt");
            break;
        case 18:
            strcpy(archivo, "DataBase/20.txt");
            break;
        case 19:
            strcpy(archivo, "DataBase/21.txt");
            break;
        case 20:
            strcpy(archivo, "DataBase/22.txt");
            break;
        case 21:
            strcpy(archivo, "DataBase/23.txt");
            break;
    }

    // Se abre el archivo
    FILE *file = fopen(archivo, "r");

    // Se verifica que el archivo exista
    if(file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        system("pause");
        exit(1);
    }

    // Se inicializa la semilla para generar números aleatorios
    srand(time(NULL));

    // Se crea un buffer para almacenar la palabra
    char buffer[100];

    // Se recorre el archivo
    while(fgets(buffer, 100, file))
    {
        // Se obtiene un número aleatorio
        int aleatorio = rand() % totalPalabras;

        // Se saltan las palabras hasta llegar al número aleatorio
        for(int i = 0; i < aleatorio; i++)
        {
            fgets(buffer, 100, file);
        }

        // Se elimina el salto de linea
        buffer[strlen(buffer) - 1] = '\0';

        // Se crea una struct para almacenar la palabra
        Palabra *palabra = (Palabra *) malloc(sizeof(Palabra));

        // Se asigna la palabra a la struct
        strcpy(palabra->palabra, buffer);

        // Se asigna el nivel a la struct
        palabra->nivel = jugador->nivel;

        // Se verifica que la palabra no haya sido jugada
        if(searchMap(jugador->palabrasJugadas, palabra->palabra) == NULL)
        {
            // Se agrega la palabra al mapa
            insertMap(jugador->palabrasJugadas, palabra->palabra, palabra);

            // Se asigna la palabra secreta
            strcpy(nivel->palabraSecreta, buffer);

            break;
        }
        else
        {
            // Se vuelven al inicio del archivo
            rewind(file);
        }
    }

    // Se cierra el archivo
    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sobrescribirLinea(char* nombreArchivo, int numeroLinea, const char* nuevaLinea) {
    // Abrir el archivo en modo lectura
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Crear un archivo temporal para escribir el contenido actualizado
    FILE* archivoTemporal = fopen("temp.txt", "w");
    if (archivoTemporal == NULL) {
        printf("No se pudo crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    // Variables para contar las líneas y almacenar el contenido de cada línea
    char linea[100];
    int numeroLineaActual = 0;

    // Leer el archivo línea por línea
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        numeroLineaActual++;

        // Si es la línea que deseamos sobrescribir, la reemplazamos con la nueva línea
        if (numeroLineaActual == numeroLinea) {
            fputs(nuevaLinea, archivoTemporal);
        } else {
            fputs(linea, archivoTemporal);
        }
    }

    // Cerrar los archivos
    fclose(archivo);
    fclose(archivoTemporal);

    // Eliminar el archivo original
    remove(nombreArchivo);

    // Renombrar el archivo temporal con el nombre original
    rename("temp.txt", nombreArchivo);
}

void guardarPartida(Jugador *jugador, int x, int y)
{
    // Abrir el archivo de guardado
    FILE *archivo = fopen("partida_guardada.txt", "r");

    // Se crea un booleano para saber si el jugador ya existe
    bool existe = false;

    // Verificar si el archivo existe
    if (archivo != NULL)
    {
        char linea[50];
        char *nombre;

        // Recorrer el archivo
        int numeroLinea = 0;
        while (fgets(linea, sizeof(linea), archivo))
        {
            numeroLinea++;

            // Se separa el nombre del jugador del resto de la línea separada por comas
            nombre = strtok(linea, ",");

            // Si el nombre del jugador es igual al nombre del archivo, el jugador ya existe
            if (strcmp(nombre, jugador->nombre) == 0)
            {
                // Se cierra el archivo
                fclose(archivo);

                // Se sobrescribe la línea con los datos actualizados del jugador
                char nuevaLinea[100];
                snprintf(nuevaLinea, sizeof(nuevaLinea), "%s,%d,%d\n", jugador->nombre, jugador->puntos, jugador->nivel);
                sobrescribirLinea("partida_guardada.txt", numeroLinea, nuevaLinea);

                // Se marca que el jugador ya existe
                existe = true;

                break;
            }
        }

        // Cerrar el archivo
        fclose(archivo);
    }

    // Si el jugador no existe, se agrega al final del archivo
    if (!existe)
    {
        // Abrir el archivo en modo escritura al final
        archivo = fopen("partida_guardada.txt", "a");
        if (archivo == NULL)
        {
            printf("No se pudo abrir el archivo.\n");
            return;
        }

        fprintf(archivo, "%s,%d,%d\n", jugador->nombre, jugador->puntos, jugador->nivel);

        // Cerrar el archivo
        fclose(archivo);
    }

    // Se muestra un mensaje de confirmación
    gotoxy(x, y);
    printf("Partida guardada exitosamente.");
}

void cargarPartida(char *nombreJugador, Jugador *jugador, int x, int y)
{
    // Abrir el archivo de guardado
    FILE *archivo = fopen("partida_guardada.txt", "r");

    // Verificar si el archivo existe
    if (archivo == NULL)
    {
        // El archivo no existe, mostrar un mensaje de error
        gotoxy(x, y);
        printf("No se encontró ninguna partida guardada.\n");

        return;
    }

    // Crear un buffer para almacenar la línea
    char linea[50];

    // Crear un booleano para saber si el jugador fue encontrado
    bool encontrado = false;

    // Recorrer el archivo
    while (fgets(linea, sizeof(linea), archivo))
    {
        // Se separa el nombre del jugador del resto de la línea separada por comas
        char *nombre = strtok(linea, ",");

        // Si el nombre del jugador es igual al nombre del archivo, el jugador ya existe
        if (strcmp(nombre, nombreJugador) == 0)
        {
            // Se marca que el jugador fue encontrado
            encontrado = true;

            // Se separa el puntaje del resto de la línea separada por comas
            char *puntaje = strtok(NULL, ",");

            // Se separa el nivel del resto de la línea separada por comas
            char *nivel = strtok(NULL, ",");

            // Se asigna el nombre del jugador
            strcpy(jugador->nombre, nombre);

            // Se asigna el puntaje del jugador
            jugador->puntos = atoi(puntaje);

            // Se asigna el nivel del jugador
            jugador->nivel = atoi(nivel);

            // Se cierra el archivo
            fclose(archivo);

            // Se muestra un mensaje de confirmación
            gotoxy(x, y);
            printf("Partida cargada exitosamente.");

            return;
        }
    }

    // Cerrar el archivo
    fclose(archivo);

    // Verificar si el jugador fue encontrado
    if (!encontrado)
    {
        // El jugador no fue encontrado, mostrar un mensaje de error
        gotoxy(x, y);
        printf("No se encontró ninguna partida para el jugador '%s'.\n", nombreJugador);

        return;
    }
}

// Funcion para obtener todas las partidas guardadas y almacenarlas en un arreglo
void obtenerJugadores(ArrayList *jugadores)
{
    // Abrir el archivo de guardado
    FILE *archivo = fopen("partida_guardada.txt", "r");

    // Verificar si el archivo existe
    if (archivo == NULL)
    {
        // El archivo no existe, mostrar un mensaje de error
        printf("No se encontró ninguna partida guardada.\n");

        return;
    }

    // Crear un buffer para almacenar la línea
    char linea[50];

    // Recorrer el archivo
    while (fgets(linea, sizeof(linea), archivo))
    {
        // Se separa el nombre del jugador del resto de la línea separada por comas
        char *nombre = strtok(linea, ",");

        // Se separa el puntaje del resto de la línea separada por comas
        char *puntaje = strtok(NULL, ",");

        // Se separa el nivel del resto de la línea separada por comas
        char *nivel = strtok(NULL, ",");

        // Se crea una struct para almacenar el jugador
        Jugador *jugador = (Jugador *)malloc(sizeof(Jugador));

        // Se asigna el nombre del jugador
        strcpy(jugador->nombre, nombre);

        // Se asigna el puntaje del jugador
        jugador->puntos = atoi(puntaje);

        // Se asigna el nivel del jugador
        jugador->nivel = atoi(nivel);

        // Se agrega el jugador al arreglo
        append(jugadores, jugador);
    }

    // Cerrar el archivo
    fclose(archivo);
}