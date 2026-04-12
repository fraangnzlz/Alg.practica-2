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


template <typename T>
inline static void quicksort(T Tvec[], int num_elem);

template <typename T>
static void quicksort_lims(T Tvec[], int inicial, int final);

template <typename T>
inline static void insercion(T Tvec[], int num_elem);

template <typename T>
static void insercion_lims(T Tvec[], int inicial, int final);

template <typename T>
static void dividir_qs(T Tvec[], int inicial, int final, int &pp);

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

   @param T: vector de elementos. Tiene un nmero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posicin que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posicin detrs de la ltima de la parte del
                   vector a ordenar.
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo quicksort.
*/
static void quicksort_lims(string T[], int inicial, int final);


/**
   @brief Ordena un vector por el mtodo de insercin.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: nmero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de insercin.
*/
inline static
void insercion(string T[], int num_elem);


/**
   @brief Ordena parte de un vector por el mtodo de insercin.

   @param T: vector de elementos. Tiene un nmero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posicin que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posicin detrs de la ltima de la parte del
                   vector a ordenar.
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de insercin.
*/
static void insercion_lims(string T[], int inicial, int final);


/**
   @brief Redistribuye los elementos de un vector segn un pivote.

   @param T: vector de elementos. Tiene un nmero de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posicin que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posicin detrs de la ltima de la parte del
                   vector a ordenar.
		   inicial < final.
   @param pp: Posicin del pivote. Es MODIFICADO.

   Selecciona un pivote los elementos de T situados en las posiciones
   entre inicial y final - 1. Redistribuye los elementos, situando los
   menores que el pivote a su izquierda, despus los iguales y a la
   derecha los mayores. La posicin del pivote se devuelve en pp.
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


template <typename T>
inline static void insercion(T Tvec[], int num_elem)
{
  insercion_lims(Tvec, 0, num_elem);
}

template <typename T>
static void insercion_lims(T Tvec[], int inicial, int final)
{
  int i, j;
  T aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((Tvec[j] < Tvec[j-1]) && (j > 0)) {
      aux = Tvec[j];
      Tvec[j] = Tvec[j-1];
      Tvec[j-1] = aux;
      j--;
    };
  };
}

int UMBRAL_QS = 256;

template <typename T>
inline static void quicksort(T Tvec[], int num_elem)
{
  quicksort_lims(Tvec, 0, num_elem);
}

template <typename T>
static void quicksort_lims(T Tvec[], int inicial, int final)
{
  int k;
  if (final - inicial < UMBRAL_QS) {
    insercion_lims(Tvec, inicial, final);
  } else {
    dividir_qs(Tvec, inicial, final, k);
    quicksort_lims(Tvec, inicial, k);
    quicksort_lims(Tvec, k + 1, final);
  };
}

template <typename T>
static void dividir_qs(T Tvec[], int inicial, int final, int & pp)
{
  T pivote, aux;
  int k, l;

  pivote = Tvec[inicial];
  k = inicial;
  l = final;
  do {
    k++;
  } while ((Tvec[k] <= pivote) && (k < final-1));
  do {
    l--;
  } while (Tvec[l] > pivote);
  while (k < l) {
    aux = Tvec[k];
    Tvec[k] = Tvec[l];
    Tvec[l] = aux;
    do k++; while (Tvec[k] <= pivote);
    do l--; while (Tvec[l] > pivote);
  };
  aux = Tvec[inicial];
  Tvec[inicial] = Tvec[l];
  Tvec[l] = aux;
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

void primerPrueba(const int a, const int b, const int paso, const string algoritmo) {


  for (int i = a; i <= b; i+=paso) {
    //reservar 5 vectores:
    int *Enteros = new int[i];
    string *FijoPequeno = new string[i];
    string *FijoGrande = new string[i];
    string *Variable = new string[i];
    string *Prefijo = new string[i];

    //inicializar vectores
    // srand(time(0));
    // string prefijo = CalcularPrefijo(i);

    //ordenarlos

    if (algoritmo == "quicksort") {
      quicksort(Enteros,i);
    }else if (algoritmo == "mergesort") {

    }else if (algoritmo == "insercion") {

    }

    //librerar espacio
    delete [] Enteros;
    delete [] FijoPequeno;
    delete [] FijoGrande;
    delete [] Variable;
    delete [] Prefijo;

  }

}

int main(int argc, char * argv[]) {

  if (argc != 2) {
    cerr << "\nUso: " << argv[0] << " <algoritmo>\n"
         << "Algoritmos validos: mergesort, quicksort, insercion" << endl;
    return -1;
  }

  string algoritmo = argv[1];

  if (algoritmo != "mergesort" && algoritmo != "quicksort" && algoritmo != "insercion") {
    cerr << "ERROR: algoritmo no valido";
    cerr << "\nUso: " << argv[0] << " <algoritmo>\n";
    return -1;
  }

  int opcion = 0;
  cout << endl << "Elige el tipo de experimento:" << endl;
  cout << "  1) Umbral fijo con numero de elementos variable" << endl;
  cout << "  2) Umbral variable con numero de elementos fijo" << endl;
  cout << "Opcion: ";
  cin >> opcion;

  if (opcion != 1 && opcion != 2) {
    cerr << "Error: opcion no valida." << endl;
    return -1;
  }

  if (opcion == 1) { //Umbral fijo, N variable
    cout << "Umbral: ";
    cin >> UMBRAL_QS;
    cout << endl << "[a,b] =  ";
    int a, b, paso;
    cin >> a >> b;
    cout << endl << "Introduzca el paso: ";
    cin >> paso;
    assert(a<b && paso >= 1 && paso <= b-a);

    primerPrueba(a,b,paso, algoritmo);

  } else { //N fijo, Umbral Variable

  }

  return 0;
}
