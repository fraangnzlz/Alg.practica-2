#!/bin/bash

# ==========================================
# CONFIGURACIÓN DEL EXPERIMENTO
# ==========================================
PROGRAMA="./mergesort"   # Cambia a "./quicksort" para probar el otro algoritmo
N_ELEMENTOS=1000000      # Usa 1000000 para umbrales. Usa 10000 o 50000 para Inserción.
TIPO_STRING=1            # 1 = Fijo | 2 = Variable | 3 = Prefijo Comun
ALGORITMO=0              # 0 = Divide y Vencerás (Merge/Quick) | 1 = Inserción Pura
REPETICIONES=5           # Veces que se repite cada prueba para sacar la media

# Lista de umbrales a probar (según pide el guion)
UMBRALES=(2 4 8 16 32 64 128 256)

echo "Iniciando pruebas..."
echo "Programa: $PROGRAMA | Elementos: $N_ELEMENTOS | Tipo String: $TIPO_STRING | Algoritmo: $ALGORITMO"
echo "---------------------------------------------------------"
echo "Umbral, Tiempo_Medio_ms"

# Bucle que recorre cada umbral
for UMBRAL in "${UMBRALES[@]}"; do
    SUMA=0
    for i in $(seq 1 $REPETICIONES); do
        # Ejecutamos el programa pasándole los 4 argumentos requeridos
        SALIDA=$($PROGRAMA $N_ELEMENTOS $UMBRAL $TIPO_STRING $ALGORITMO)

        # Extraemos solo el número del tiempo (es la palabra número 14 de la salida)
        TIEMPO=$(echo $SALIDA | awk '{print $14}')

        # Sumamos los tiempos (usamos bc para los decimales)
        SUMA=$(echo "$SUMA + $TIEMPO" | bc -l)
    done

    # Calculamos la media
    MEDIA=$(echo "scale=4; $SUMA / $REPETICIONES" | bc -l)

    # Imprimimos el resultado en formato tabla (fácil para Excel)
    echo "$UMBRAL, $MEDIA"
done

echo "---------------------------------------------------------"