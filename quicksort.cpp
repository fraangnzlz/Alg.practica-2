/**
   @file Ordenaci�n r�pida (quicksort).
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <string>
#include <chrono>


/* ************************************************************ */ 
/*  M�todo de ordenaci�n r�pida  */

/**
   @brief Ordena un vector por el m�todo quicksort.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo quicksort.
*/
inline static 
void quicksort(string T[], int num_elem);


/**
   @brief Ordena parte de un vector por el m�todo quicksort.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo quicksort.
*/
static void quicksort_lims(string T[], int inicial, int final);


/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
inline static 
void insercion(string T[], int num_elem);


/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
static void insercion_lims(string T[], int inicial, int final);


/**
   @brief Redistribuye los elementos de un vector seg�n un pivote.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.
   @param pp: Posici�n del pivote. Es MODIFICADO.

   Selecciona un pivote los elementos de T situados en las posiciones
   entre inicial y final - 1. Redistribuye los elementos, situando los
   menores que el pivote a su izquierda, despu�s los iguales y a la
   derecha los mayores. La posici�n del pivote se devuelve en pp.
*/
static void dividir_qs(string T[], int inicial, int final, int & pp);



/**
   Implementaci�n de las funciones
**/


inline static void insercion(string T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(string T[], int inicial, int final)
{
  int i, j;
  string aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_QS = 256;


inline void quicksort(string T[], int num_elem)
{
  quicksort_lims(T, 0, num_elem);
}

static void quicksort_lims(string T[], int inicial, int final)
{
  int k;
  if (final - inicial < UMBRAL_QS) {
    insercion_lims(T, inicial, final);
  } else {
    dividir_qs(T, inicial, final, k);
    quicksort_lims(T, inicial, k);
    quicksort_lims(T, k + 1, final);
  };
}


static void dividir_qs(string T[], int inicial, int final, int & pp)
{
  string pivote, aux;
  int k, l;

  pivote = T[inicial];
  k = inicial;
  l = final;
  do {
    k++;
  } while ((T[k] <= pivote) && (k < final-1));
  do {
    l--;
  } while (T[l] > pivote);
  while (k < l) {
    aux = T[k];
    T[k] = T[l];
    T[l] = aux;
    do k++; while (T[k] <= pivote);
    do l--; while (T[l] > pivote);
  };
  aux = T[inicial];
  T[inicial] = T[l];
  T[l] = aux;
  pp = l;
};



//FUNCIONES PARA GENERAR VECTORES DE TAMAÑO FIJOS Y VARIABLE Y CON PREFIJOS


//TAMAÑO FIJO
string StringFijo(int longitud){
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado = "";
  
  for(int i = 0; i < longitud;++i){
    resultado += caracteres[rand() % caracteres.length()];
  }

  return resultado;
}

//TAMAÑO VARIABLE
string StringVariable(int longitud_minima, int longitud_maxima){
  string caracteres = "abdefghiklmnopqrstuvwxyz";
  string resultado = "";

  //Calculamos una longitud aleatoria para el vector
  int longitud = longitud_minima + rand() % (longitud_maxima - longitud_minima + 1); //+1!!
  for(int i = 0; i < longitud;i++){
    resultado += caracteres[rand() % caracteres.length()];
  }

  return resultado;
}


//CON PREFIJOS
string StringPrefijo(string prefijo, int longitud_anadida){
  string caracteres = "abdefghiklmnopqrstuvwxyz";
  string resultado = "";

  for(int i = 0; i < longitud_anadida;++i){
    resultado += caracteres[rand() % caracteres.length()];
  }

  return resultado;
}

int main(int argc, char * argv[]){

  //Comprobacion de argumentos
  if(argc != 2){
    cerr << "\nError, introduce la cantidad correcta de argumentos" << endl;
    return -1;
  }

  //Pasamos con cast el argumento a entero
  int a = atoi(argv[1]);

  //Llamamos a la funcion para crear un vector dinámico
  string * V = new string[a];
  assert(V);

  srand(time(0));

  //Llenamos el vector
  for(int i = 0; i < a; i++){
    //V[i] = StringFijo(50);


    V[i] = StringVariable(10,100);


    //V[i] = StringPrefijo("prefijo_largo_para_prueba",10);

  }

  //Calculamos el tiempo
  auto start = chrono::high_resolution_clock::now();

  quicksort(V,a);

  //Tiempo final
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double,std::milli> duration = end - start; //Calculamos el tiempo que tarda

  //Resultados:
  cout << "\nQuicksort ejecutado para:" << a << endl;
  cout << "\nUmbral utilizado: " << UMBRAL_QS << endl;
  cout << "\nTiempo de ejecucion: " << duration.count() << " milisegundos" << endl;
  
  //Liberamos memoria
  delete [] V;

  return 0;

}

