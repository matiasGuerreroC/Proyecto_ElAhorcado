#!/bin/bash

# Script para compilar el programa desde git bash

# Ingresar el nombre del ejecutable
read -p "Ingrese el nombre del ejecutable: " executable

# Archivos a compilar
FILES="main.c Struct/struct.h BackEnd/backend.c FrontEnd/frontend.c DataStructures/Map/Map.c DataStructures/ArrayList/arraylist.c DataStructures/List/list.c DataStructures/TreeMap/treemap.c"

# Compilacion con gcc
gcc -g $FILES -o $executable -lwinmm

# Verificar si hubo errores
if [ $? -eq 0 ]; then
    echo "Compilacion exitosa"
else
    echo "Hubo errores en la compilacion"
fi

# Ejectuar el programa en una ventana nueva
# cmd.exe /c $executable.exe