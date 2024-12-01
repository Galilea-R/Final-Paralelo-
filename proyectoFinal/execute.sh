#!/bin/bash

# Compilacion del programa serial
echo "Compilando el programa serial..."
g++ -std=c++11 -o serial serial.cpp
if [ $? -ne 0 ]; then
    echo "Falla al compilar el programa serial"
    exit 1
fi

# Compilacion del programa paralelo
echo "Compilando el programa paralelo..."
mpicxx -std=c++11 -o parallel parallel.cpp
if [ $? -ne 0 ]; then
    echo "Falla al compilar el programa paralelo"
    exit 1
fi

# Limpieza y almacenamiento de los libros en vocab
echo "Limpiando libros y almacenando en vocabulary.csv..."
python3 limpia_libros.py

# Corre version serial
echo "Corriendo version serial..."
./serial
if [ $? -ne 0 ]; then
    echo "Falla al ejecutar el programa serial"
    exit 1
fi

# Corre version paralela con 6 procesos
echo "Corriendo version paralelo con 6 procesos"
mpiexec -n 6 ./parallel
if [ $? -ne 0 ]; then
    echo "Falla al ejecutar el programa paralelo"
    exit 1
fi

# Plot execution times
echo "Graficando tiempos de ejecucion..."
python3 grafica.py
