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
#include "../DataStructures/TreeMap/treemap.h"

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
    if(jugador->idioma == 1)
    {
        char archivo[20];

        int totalPalabras;

        // Se verifica el nivel seleccionado
        switch(jugador->nivel)
        {
            case 1:
                strcpy(archivo, "DataBase/03.txt");
                totalPalabras = 104;
                break;
            case 2:
                strcpy(archivo, "DataBase/04.txt");
                totalPalabras = 157;
                break;
            case 3:
                strcpy(archivo, "DataBase/05.txt");
                totalPalabras = 140;
                break;
            case 4:
                strcpy(archivo, "DataBase/06.txt");
                totalPalabras = 142;
                break;
            case 5:
                strcpy(archivo, "DataBase/07.txt");
                totalPalabras = 180;
                break;
            case 6:
                strcpy(archivo, "DataBase/08.txt");
                totalPalabras = 157;
                break;
            case 7:
                strcpy(archivo, "DataBase/09.txt");
                totalPalabras = 159;
                break;
            case 8:
                strcpy(archivo, "DataBase/10.txt");
                totalPalabras = 164;
                break;
            case 9:
                strcpy(archivo, "DataBase/11.txt");
                totalPalabras = 135;
                break;
            case 10:
                strcpy(archivo, "DataBase/12.txt");
                totalPalabras = 143;
                break;
            case 11:
                strcpy(archivo, "DataBase/13.txt");
                totalPalabras = 152;
                break;
            case 12:
                strcpy(archivo, "DataBase/14.txt");
                totalPalabras = 176;
                break;
            case 13:
                strcpy(archivo, "DataBase/15.txt");
                totalPalabras = 142;
                break;
            case 14:
                strcpy(archivo, "DataBase/16.txt");
                totalPalabras = 104;
                break;
            case 15:
                strcpy(archivo, "DataBase/17.txt");
                totalPalabras = 71;
                break;
            case 16:
                strcpy(archivo, "DataBase/18.txt");
                totalPalabras = 35;
                break;
            case 17:
                strcpy(archivo, "DataBase/19.txt");
                totalPalabras = 10;
                break;
            case 18:
                strcpy(archivo, "DataBase/20.txt");
                totalPalabras = 3;
                break;
            case 19:
                strcpy(archivo, "DataBase/21.txt");
                totalPalabras = 5;
                break;
            case 20:
                strcpy(archivo, "DataBase/22.txt");
                totalPalabras = 3;
                break;
            case 21:
                strcpy(archivo, "DataBase/23.txt");
                totalPalabras = 1;
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

            // Se separa la palabra hasta la coma
            char *token = strtok(buffer, ",");

            // Se obtiene la pista hasta el salto de linea
            char *pista = strtok(NULL, "\n");

            // Se quitan las tildes de la pistas
            pista = quitar_tildes(pista);

            // Se crea una struct para almacenar la palabra
            Palabra *palabra = (Palabra *) malloc(sizeof(Palabra));

            // Se asigna la palabra a la struct
            strcpy(palabra->palabra, token);

            // Se asigna la pista a la struct
            strcpy(palabra->pista, pista);

            // Se asigna el nivel a la struct
            palabra->nivel = jugador->nivel;

            // Se verifica que la palabra no haya sido jugada
            if(searchMap(jugador->palabrasJugadas, palabra->palabra) == NULL)
            {
                // Se agrega la palabra al mapa
                insertMap(jugador->palabrasJugadas, palabra->palabra, palabra);

                // Se asigna la palabra secreta
                strcpy(nivel->palabraSecreta, buffer);

                // Se asigna la pista
                strcpy(nivel->pista, pista);

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
    else if (jugador->idioma == 2)
    {
        char archivo[20];

        int totalPalabras;

        // Se verifica el nivel seleccionado
        switch(jugador->nivel)
        {
            case 1:
                strcpy(archivo, "WordBank/03_English.txt");
                totalPalabras = 171;
                break;
            case 2:
                strcpy(archivo, "WordBank/04_English.txt");
                totalPalabras = 100;
                break;
            case 3:
                strcpy(archivo, "WordBank/05_English.txt");
                totalPalabras = 170;
                break;
            case 4:
                strcpy(archivo, "WordBank/06_English.txt");
                totalPalabras = 136;
                break;
            case 5:
                strcpy(archivo, "WordBank/07_English.txt");
                totalPalabras = 148;
                break;
            case 6:
                strcpy(archivo, "WordBank/08_English.txt");
                totalPalabras = 164;
                break;
            case 7:
                strcpy(archivo, "WordBank/09_English.txt");
                totalPalabras = 101;
                break;
            case 8:
                strcpy(archivo, "WordBank/10_English.txt");
                totalPalabras = 100;
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

            // Se separa la palabra hasta la coma
            char *token = strtok(buffer, ",");

            // Se obtiene la pista hasta el salto de linea
            char *pista = strtok(NULL, "\n");

            // Se quitan las tildes de la pistas
            pista = quitar_tildes(pista);

            // Se crea una struct para almacenar la palabra
            Palabra *palabra = (Palabra *) malloc(sizeof(Palabra));

            // Se asigna la palabra a la struct
            strcpy(palabra->palabra, token);

            // Se asigna la pista a la struct
            strcpy(palabra->pista, pista);

            // Se asigna el nivel a la struct
            palabra->nivel = jugador->nivel;

            // Se verifica que la palabra no haya sido jugada
            if(searchMap(jugador->palabrasJugadas, palabra->palabra) == NULL)
            {
                // Se agrega la palabra al mapa
                insertMap(jugador->palabrasJugadas, palabra->palabra, palabra);

                // Se asigna la palabra secreta
                strcpy(nivel->palabraSecreta, buffer);

                // Se asigna la pista
                strcpy(nivel->pista, pista);

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
}

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
    FILE *archivo = fopen("partidas_guardadas.txt", "r");

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
                sobrescribirLinea("partidas_guardadas.txt", numeroLinea, nuevaLinea);

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
        archivo = fopen("partidas_guardadas.txt", "a");
        
        if (archivo == NULL)
        {
            if(jugador->idioma == 1) //Español
            {
                printf("No se pudo abrir el archivo.\n");
                return;
            }
            else if(jugador->idioma == 2) //Inglés
            {
                printf("The file could not be opened.\n");
                return;
            }
        }

        fprintf(archivo, "%s,%d,%d\n", jugador->nombre, jugador->puntos, jugador->nivel);

        // Cerrar el archivo
        fclose(archivo);
    }

    // Se muestra un mensaje de confirmación
    gotoxy(x, y);
    if(jugador->idioma == 1) //Español
    {
        printf("Partida guardada exitosamente.");
    }
    else if(jugador->idioma == 2) //Inglés
    {
        printf("Game saved successfully.");
    }
}

void cargarPartida(char *nombreJugador, Jugador *jugador, int x, int y)
{
    // Abrir el archivo de guardado
    FILE *archivo = fopen("partidas_guardadas.txt", "r");

    // Verificar si el archivo existe
    if (archivo == NULL)
    {
        // El archivo no existe, mostrar un mensaje de error
        gotoxy(x, y);
        if(jugador->idioma == 1)
        {
            printf("No se encontró ninguna partida guardada.\n");
        }
        else if(jugador->idioma == 2)
        {
            printf("No saved game was found.\n");
        }

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
            if(jugador->idioma == 1) //Español
            {
                printf("Partida cargada exitosamente.");
            }
            else if(jugador->idioma == 2) //Inglés
            {
                printf("Game loaded successfully.");
            }

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
        if(jugador->idioma == 1) //Español
        {
            printf("No se encontró ninguna partida para el jugador '%s'.\n", nombreJugador);
        }
        else if(jugador->idioma == 2) //Inglés
        {
            printf("No game was found for the player '%s'.\n", nombreJugador);
        }
        return;
    }
}

// Funcion para obtener todas las partidas guardadas y almacenarlas en un arreglo
void obtenerJugadores(ArrayList *jugadores, Jugador *jugador)
{
    if(jugador->idioma == 1) // Español
    {
        // Abrir el archivo de guardado
        FILE *archivo = fopen("partidas_guardadas.txt", "r");

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
    else if(jugador->idioma == 2) // Ingles
    {
        // Abrir el archivo de guardado
        FILE *archivo = fopen("partidas_guardadas.txt", "r");

        // Verificar si el archivo existe
        if (archivo == NULL)
        {
            // El archivo no existe, mostrar un mensaje de error
            printf("No saved games found.\n");

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
}

//====================================================================================================
// Funciones para administracion de los puntajes
//====================================================================================================

//bool que sirve para verificar si califica para el top 10
int calificaEnTabla(TreeMap *tree, int puntos)
{   

    if(puntos == 0) //si no tiene puntos no califica en la tabla
    {   
        return 0;
    }

    //conseguimos al ultimo de la lista
    Pair *aux_pair = firstTreeMap(tree);

    if(aux_pair == NULL)
    {   
        return 1;
    }

    if(treeSize(tree) < 10)
    {
        return 1;
    }
     

    Jugador *current_last_spot = (Jugador*) aux_pair->value; 
    
    //verificamos si el puntaje del jugador actual es mayor a el ultimo puesto
    if(puntos > current_last_spot->puntos)
    {
        return 1;
    }

    return 0;
}

//verifica si el jugador existe en la tabla para evitar nombres
int JugadorExisteEnTabla(TreeMap *tree, char* nombre)
{   
   
    Pair *aux_pair = firstTreeMap(tree);
    Jugador *current_spot = (Jugador*) aux_pair->value;

    while(aux_pair != NULL)
    {   
        if(strcmp(nombre, current_spot->nombre) == 0)
        {
            return 1;
        }
        else
        {
            aux_pair = nextTreeMap(tree);

            if(aux_pair == NULL) return 0;

            current_spot = (Jugador*) aux_pair->value;
        }
    }
}

//procesamos el nombre repetido, si el puntaje nuevo es mayor
void procesarJugadorRepetido(TreeMap *tree, Jugador * player)
{   
    //tomamos la ultima posicion de la tabla
    Pair *aux_pair = firstTreeMap(tree);
    
    //recorremos la tabla
    while(aux_pair != NULL)
    {   
        Jugador *current_spot = (Jugador*) aux_pair->value;

        //si es el mismo nombre, evaluamos
        if(strcmp(player->nombre, current_spot->nombre) == 0)
        {   
            //si supera los puntos del mismo nombre, se elimina el que existe en la lista y se inserta el con puntaje mas alto
            if(current_spot->puntos < player->puntos)
            {
                eraseTreeMapCurrent(tree);
                insertTreeMap(tree, (void *) player->puntos, (void *) player);
            }
            return;

        }
        else
        {   
            //recorre al siguiente de la lista
            aux_pair = nextTreeMap(tree);
        }
    }
    
}

//funcion para guardar un puntaje
void guardarPuntaje(TreeMap *tree, Jugador *player)
{   

    Jugador *nuevo_jugador = (Jugador *)malloc(sizeof(Jugador));
    strcpy(nuevo_jugador->nombre, player->nombre);
    nuevo_jugador->puntos = player->puntos;

    //pregunta si es mayor a el top 10 de los puntajes
    if(calificaEnTabla(tree, nuevo_jugador->puntos) == 1)
    {   
        //si es que existe el jugador en la tabla, se comparan los puntajes de ambos casos
        if(JugadorExisteEnTabla(tree, nuevo_jugador->nombre) == 1)
        {   

            //inserta el nuevo puntaje del jugador en la tabla en caso de ser mayor al existente, en caso contrario solo se omite
            procesarJugadorRepetido(tree, nuevo_jugador);
        }
        else
        {   
            
            //al insertar un nuevo jugador, si es que este llega a crear un size de mas de 10 en la tabla, el ultimo dato se elimina.
            if(treeSize(tree) == 10)
            {   
                firstTreeMap(tree);
                eraseTreeMapCurrent(tree);
                insertTreeMap(tree, (void*) nuevo_jugador->puntos, nuevo_jugador);
            }
            else
            {
                insertTreeMap(tree, (void*) nuevo_jugador->puntos, nuevo_jugador);
            }


        }
    }
}

//funcion para leer los puntajes desde el archivo scoreboard.txt
void leerPuntajes(TreeMap* arbol_puntajes, Jugador *jugador)
{
    if(jugador->idioma == 1) // Español
    {
        FILE *archivo = fopen("scoreboard.txt", "r");

        if(archivo == NULL)
        {
            printf("No se pudo abrir el archivo\n");
            system("pause");

            return;
        }

        char linea[100];

        while(fgets(linea, 100, archivo))
        {
            Jugador *nuevo_jugador = (Jugador*) malloc(sizeof(Jugador));

            char* nombre = strtok(linea, ",");
            char* puntos = strtok(NULL, ",");

            strcpy(nuevo_jugador->nombre, nombre);
            nuevo_jugador->puntos = atoi(puntos);

            insertTreeMap(arbol_puntajes, (void *) nuevo_jugador->puntos, (void *) nuevo_jugador);
        }

        fclose(archivo);
    }
    else if(jugador->idioma == 2) // Ingles
    {
        FILE *archivo = fopen("scoreboard.txt", "r");

        if(archivo == NULL)
        {
            printf("Could not open file\n");
            system("pause");

            return;
        }

        char linea[100];

        while(fgets(linea, 100, archivo))
        {
            Jugador *nuevo_jugador = (Jugador*) malloc(sizeof(Jugador));

            char* nombre = strtok(linea, ",");
            char* puntos = strtok(NULL, ",");

            strcpy(nuevo_jugador->nombre, nombre);
            nuevo_jugador->puntos = atoi(puntos);

            insertTreeMap(arbol_puntajes, (void *) nuevo_jugador->puntos, (void *) nuevo_jugador);
        }
    }
}

//se exportan los puntajes del arbol al archivo scoreboard.txt
void exportarPuntajes(TreeMap* arbol_puntajes)
{
    //se abre el archivo para leer los datos
    FILE * archivo = fopen("scoreboard.txt", "w");

    if(archivo == NULL) // Si el archivo no se creo correctamente
    {
        // Se muestra un mensaje de error
        puts("\n========================================");
        puts("   El archivo no se creo correctamente");
        puts("========================================");
    }
    else
    {
        Pair* aux_pair = firstTreeMap(arbol_puntajes);

        while(aux_pair != NULL)
        {   
            Jugador *current_spot = (Jugador*) aux_pair->value;


            fprintf(archivo, "%s,%d\n", current_spot->nombre, current_spot->puntos);


            aux_pair = nextTreeMap(arbol_puntajes);
        }
    }

    fclose(archivo);

}