#!/bin/bash

# Configuración
PROGRAMA="./quicksort"
N_ELEMENTOS=1000000
REPETICIONES=10
SUMA=0

for i in $(seq 1 $REPETICIONES); do
    # Ejecuta y extrae el número
    TIEMPO=$($PROGRAMA $N_ELEMENTOS | grep "Tiempo" | awk '{print $4}')
    
    # Muestra el tiempo individual
    echo "Ejecución $i: $TIEMPO ms"
    
    # Suma los tiempos (usamos 'bc' para manejar decimales)
    SUMA=$(echo "$SUMA + $TIEMPO" | bc -l)
done

# Calcula la media
MEDIA=$(echo "scale=4; $SUMA / $REPETICIONES" | bc -l)

echo "-----------------------------------------------"
echo "MEDIA TOTAL: $MEDIA milisegundos"