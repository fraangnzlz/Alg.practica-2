#!/bin/bash

# =========================================================================
# SCRIPT MAESTRO - PRÁCTICA 2 ALGORÍTMICA
# =========================================================================

# Archivo donde se guardarán todos los datos
ARCHIVO_CSV="resultados_completos.csv"

# Escribimos la cabecera del Excel
echo "Algoritmo,Tamaño,Umbral,TipoString,TiempoMedio_ms" > $ARCHIVO_CSV

# Parámetros generales
REPETICIONES=5 # Baja a 3 si ves que tarda demasiadas horas
PROGRAMAS=("./mergesort" "./quicksort")
TIPOS_STRING=(1 2 3) # 1=Fijo, 2=Variable, 3=Prefijo

echo "========================================================="
echo "INICIANDO BATERÍA DE PRUEBAS AUTOMÁTICAS"
echo "========================================================="

# -------------------------------------------------------------------------
# FASE 1: TAMAÑOS GRANDES (Búsqueda del mejor umbral)
# -------------------------------------------------------------------------
echo ""
echo ">>> FASE 1: Evaluando Umbrales con tamaño 1.000.000"
TAMANO_GRANDE=1000000
UMBRALES=(2 4 8 16 32 64 128 256)

for PROGRAMA in "${PROGRAMAS[@]}"; do
    NOMBRE_ALG=$(basename $PROGRAMA)
    for TIPO in "${TIPOS_STRING[@]}"; do

        NOMBRE_STR="Fijo"
        if [ $TIPO -eq 2 ]; then NOMBRE_STR="Variable"; fi
        if [ $TIPO -eq 3 ]; then NOMBRE_STR="Prefijo"; fi

        echo "-> Ejecutando $NOMBRE_ALG | String: $NOMBRE_STR | Tamaño: 1M"

        for UMBRAL in "${UMBRALES[@]}"; do
            SUMA=0
            for i in $(seq 1 $REPETICIONES); do
                # Ejecutamos el algoritmo normal (parámetro final 0)
                SALIDA=$($PROGRAMA $TAMANO_GRANDE $UMBRAL $TIPO 0)
                TIEMPO=$(echo $SALIDA | awk '{print $14}')
                SUMA=$(echo "$SUMA + $TIEMPO" | bc -l)
            done
            MEDIA=$(echo "scale=4; $SUMA / $REPETICIONES" | bc -l)

            # Guardamos en el CSV y mostramos por pantalla
            echo "$NOMBRE_ALG,$TAMANO_GRANDE,$UMBRAL,$NOMBRE_STR,$MEDIA" >> $ARCHIVO_CSV
            echo "   Umbral $UMBRAL: $MEDIA ms"
        done
    done
done

# -------------------------------------------------------------------------
# FASE 2: TAMAÑOS PEQUEÑOS (Comparación con Inserción)
# -------------------------------------------------------------------------
echo ""
echo ">>> FASE 2: Evaluando Tamaños pequeños vs Inserción"
TAMANOS_PEQUENOS=(10000 20000 30000 40000 50000)
UMBRAL_FIJO=32 # Usamos un umbral promedio para MS y QS en estas pruebas

for TIPO in "${TIPOS_STRING[@]}"; do
    NOMBRE_STR="Fijo"
    if [ $TIPO -eq 2 ]; then NOMBRE_STR="Variable"; fi
    if [ $TIPO -eq 3 ]; then NOMBRE_STR="Prefijo"; fi

    echo "-> Comparando algoritmos con String: $NOMBRE_STR"

    for TAMANO in "${TAMANOS_PEQUENOS[@]}"; do

        # 1. Inserción pura (Usamos ./mergesort pero con el flag de algoritmo a 1)
        SUMA=0
        for i in $(seq 1 $REPETICIONES); do
            SALIDA=$(./mergesort $TAMANO $UMBRAL_FIJO $TIPO 1)
            TIEMPO=$(echo $SALIDA | awk '{print $14}')
            SUMA=$(echo "$SUMA + $TIEMPO" | bc -l)
        done
        MEDIA_INS=$(echo "scale=4; $SUMA / $REPETICIONES" | bc -l)
        echo "Insercion,$TAMANO,N/A,$NOMBRE_STR,$MEDIA_INS" >> $ARCHIVO_CSV

        # 2. MergeSort
        SUMA=0
        for i in $(seq 1 $REPETICIONES); do
            SALIDA=$(./mergesort $TAMANO $UMBRAL_FIJO $TIPO 0)
            TIEMPO=$(echo $SALIDA | awk '{print $14}')
            SUMA=$(echo "$SUMA + $TIEMPO" | bc -l)
        done
        MEDIA_MS=$(echo "scale=4; $SUMA / $REPETICIONES" | bc -l)
        echo "MergeSort,$TAMANO,$UMBRAL_FIJO,$NOMBRE_STR,$MEDIA_MS" >> $ARCHIVO_CSV

        # 3. QuickSort
        SUMA=0
        for i in $(seq 1 $REPETICIONES); do
            SALIDA=$(./quicksort $TAMANO $UMBRAL_FIJO $TIPO 0)
            TIEMPO=$(echo $SALIDA | awk '{print $14}')
            SUMA=$(echo "$SUMA + $TIEMPO" | bc -l)
        done
        MEDIA_QS=$(echo "scale=4; $SUMA / $REPETICIONES" | bc -l)
        echo "QuickSort,$TAMANO,$UMBRAL_FIJO,$NOMBRE_STR,$MEDIA_QS" >> $ARCHIVO_CSV

        echo "   Tamaño $TAMANO | Inserción: $MEDIA_INS ms | Merge: $MEDIA_MS ms | Quick: $MEDIA_QS ms"
    done
done

echo ""
echo "========================================================="
echo "¡TODAS LAS PRUEBAS FINALIZADAS!"
echo "Los resultados están listos en: $ARCHIVO_CSV"
echo "========================================================="