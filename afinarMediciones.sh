#!/bin/bash

# Comprobación de argumentos
if [ "$#" -ne 6 ]; then
    echo "Uso: $0 <ejecutable> <algoritmo> <umbral_inf> <umbral_sup> <tamanio> <tipo_string>"
    exit 1
fi

# Asignación de variables para mayor claridad
EJECUTABLE=$1
ALGORITMO=$2
UMBRAL_INF=$3
UMBRAL_SUP=$4
TAMANIO=$5
TIPO_STRING=$6

# Mapeo de nombres para la cabecera
case $TIPO_STRING in
    1) NOMBRE_TIPO="Fijo" ;;
    2) NOMBRE_TIPO="Variable" ;;
    3) NOMBRE_TIPO="Prefijo" ;;
    *) NOMBRE_TIPO="Desconocido" ;;
esac

# Determinar nombre del algoritmo para la cabecera
# Basado en el ejecutable y el argumento de algoritmo
NOM_ALG_CABECERA="Desconocido"
if [ "$ALGORITMO" -eq 1 ]; then
    NOM_ALG_CABECERA="Insercion"
else
    if [[ "$EJECUTABLE" == *"quicksort"* ]]; then
        NOM_ALG_CABECERA="Quicksort"
    else
        NOM_ALG_CABECERA="Mergesort"
    fi
fi

# Imprimir cabecera de presentación
echo "=========================="
echo "Algoritmo: $NOM_ALG_CABECERA"
echo "Tamaño del String: $TAMANIO"
echo "Intervalo de Umbrales: [$UMBRAL_INF,$UMBRAL_SUP]"
echo "Tipo de String: $NOMBRE_TIPO"
echo "=========================="
echo ""
printf "%-8s | %-s\n" "Umbral" "Tiempo medio (5 iteraciones cada uno)"
echo "-------------------------------------------------"

# Bucle principal sobre el intervalo de umbrales
for (( u=$UMBRAL_INF; u<=$UMBRAL_SUP; u++ ))
do
    S_TIEMPOS=0

    # Ejecutar 5 veces para calcular la media
    for i in {1..5}
    do
        # Ejecutamos y extraemos el valor numérico del tiempo usando awk
        # El formato de salida del programa es: ... | Tiempo: 123.456
        TIEMPO=$(./$EJECUTABLE $TAMANIO $u $TIPO_STRING $ALGORITMO | awk -F': ' '{print $NF}')

        # Sumamos los tiempos (usamos bc para manejar decimales si es necesario)
        S_TIEMPOS=$(echo "$S_TIEMPOS + $TIEMPO" | bc -l)
    done

    # Calcular la media (Suma / 5)
    MEDIA=$(echo "scale=6; $S_TIEMPOS / 5" | bc -l)

    # Imprimir el resultado de este umbral
    printf "%-16d %-s ms\n" "$u" "$MEDIA"
done