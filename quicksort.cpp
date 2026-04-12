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
 * @brief Genera un prefijo cuya longitud crece con el número de datos.
 *
 * @param numDatos Número de datos usado para ajustar el tamaño del prefijo.
 * @return Cadena prefijo generada.
 */
string CalcularPrefijo(const int numDatos);

/**
 * @brief Genera un entero aleatorio dentro de un rango cerrado.
 *
 * @param cota_superior Límite superior del rango.
 * @param cota_inferior Límite inferior del rango.
 * @return Entero aleatorio entre cota_inferior y cota_superior.
 */
int EnteroAleatorio(const int cota_superior, const int cota_inferior);

/**
 * @brief Genera una cadena aleatoria de longitud fija.
 *
 * @param longitud Longitud de la cadena a generar.
 * @return Cadena aleatoria formada por letras minúsculas.
 */
string StringFijo(const int longitud);

/**
 * @brief Genera una cadena aleatoria con longitud variable.
 *
 * @param longitud_minima Longitud mínima de la cadena.
 * @param longitud_maxima Longitud máxima de la cadena.
 * @return Cadena aleatoria formada por letras minúsculas.
 */
string StringVariable(const int longitud_minima, const int longitud_maxima);

/**
 * @brief Genera una cadena aleatoria a partir de un prefijo dado.
 *
 * @param prefijo Prefijo inicial de la cadena.
 * @param longitud_anadida Número de caracteres aleatorios a añadir.
 * @return Cadena resultante con el prefijo y caracteres aleatorios.
 */
string StringPrefijo(const string prefijo, const int longitud_anadida);

/**
   Implementacin de las funciones
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


int UMBRAL_QS = 256;


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

string CalcularPrefijo(const int numDatos) {
  //El prefijo debe ser proporcional al numero de datos
  string prefijo = "prefijo_proporcionalmente_largo";

  if (numDatos >= 1000) {
    int longitud = numDatos / 1000;
    for (int i = 0; i < longitud; i++)
      prefijo += "_y_se_hace_cada_vez_mas_largo_y_mas_largo_y_mas_largo";
  }
  return prefijo;
}

int EnteroAleatorio(const int cota_superior, const int cota_inferior){
  return (rand() % (cota_superior - cota_inferior + 1)) + cota_inferior;
}

//FUNCIONES PARA GENERAR VECTORES DE TAMAÑO FIJOS Y VARIABLE Y CON PREFIJOS

string StringFijo(const int longitud){
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado;
  resultado.reserve(longitud);

  for(int i = 0; i < longitud; i++){
    resultado += caracteres[rand() % caracteres.length()];
  }
  return resultado;
}

string StringVariable(const int longitud_minima, const int longitud_maxima){
  assert(longitud_maxima >= longitud_minima);
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado;
  resultado.reserve(longitud_maxima);
  int longitud = longitud_minima + rand() % (longitud_maxima - longitud_minima + 1);

  for(int i = 0; i < longitud; i++){
    resultado += caracteres[rand() % 27];
  }
  return resultado;
}


//CON PREFIJOS
string StringPrefijo(const string prefijo, const int longitud_anadida){
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado = prefijo;
  resultado.reserve(resultado.length() + longitud_anadida);

  for(int i = 0; i < longitud_anadida; i++) {
    resultado += caracteres[rand() % 26];
  }

  return resultado;
}

  int main(int argc, char * argv[]){

  //Hemos de pasarle 5 argumentos
  if(argc != 2){
    cerr << "\nUso: " << argv[0] << " <tamanio> <umbral> <tipo_string (1=Fijo, 2=Var, 3=Prefijo)> <algoritmo (0=QuickSort, 1=Insercion)>" << endl;
    return -1;
  }

  int a = atoi(argv[1]);
  UMBRAL_QS = atoi(argv[2]); // Cambiado a UMBRAL_QS
  int tipo_string = atoi(argv[3]);
  int algoritmo = atoi(argv[4]);

  assert(tipo_string == 1 || tipo_string == 2 || tipo_string == 3);
  assert(algoritmo == 0 || algoritmo == 1);

  string * V = new string[a];
  assert(V);

  srand(time(0)); //semilla
  string prefijo = CalcularPrefijo(a);

for(int i = 0; i < a; i++)
  switch (tipo_string) {
    case 1:
      V[i] = StringFijo(50);
      break;
    case 2:
      V[i] = StringVariable(5,500);
      break;
    case 3:
      V[i] = StringPrefijo(prefijo,10);
      break;
    default: break;
  }

 //Calculamos el tiempo
  auto start = chrono::high_resolution_clock::now();

  if (algoritmo)
    insercion(V,a);
  else
    quicksort(V,a); // Llamada a quicksort

  //Tiempo final
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double,std::milli> duration = end - start; //Calculamos el tiempo que tarda

  //RESULTADOS:
  string nombre_algoritmo = (algoritmo == 1) ? "Insercion" : "QuickSort"; // Etiqueta actualizada
  string nombre_string;
  if (tipo_string == 1) nombre_string = "Fijo";
  else if (tipo_string == 2) nombre_string = "Variable";
  else nombre_string = "Prefijo";

  // Formato: Algoritmo | Tamaño | Umbral | TipoString | Tiempo
  cout << "Algoritmo: " << nombre_algoritmo
       << " | Tamaño: " << a
       << " | Umbral: " << UMBRAL_QS // Cambiado a UMBRAL_QS
       << " | TipoString: " << nombre_string
       << " | Tiempo: " << duration.count() << endl;

  delete [] V;

  return 0;

}
