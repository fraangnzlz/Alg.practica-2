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

const double NUM_PRUEBAS = 10.f;

template <typename T>
static void quicksort_lims(T Tvec[], int inicial, int final);

template <typename T>
inline static void insercion(T Tvec[], int num_elem);

template <typename T>
static void insercion_lims(T Tvec[], int inicial, int final);

template <typename T>
static void dividir_qs(T Tvec[], int inicial, int final, int &pp);

// ---- NUEVO: mergesort genérico ----
template <typename T>
inline static void mergesort(T Tvec[], int num_elem);

template <typename T>
static void mergesort_lims(T Tvec[], int inicial, int final);

template <typename T>
static void fusion(T Tvec[], int inicial, int final, T U[], T V[]);


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
      Tvec[j] = Tvec[j - 1];
      Tvec[j - 1] = aux;
      j--;
    };
  };
}

int UMBRAL = 256;

template <typename T>
inline static void quicksort(T Tvec[], int num_elem)
{
  quicksort_lims(Tvec, 0, num_elem);
}

template <typename T>
static void quicksort_lims(T Tvec[], int inicial, int final)
{
  int k;
  if (final - inicial < UMBRAL) {
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
  } while ((k < final - 1) && (Tvec[k] <= pivote));
  do {
    l--;
  } while (Tvec[l] > pivote);
  while (k < l) {
    aux = Tvec[k];
    Tvec[k] = Tvec[l];
    Tvec[l] = aux;
    do k++; while ((k < final) && (Tvec[k] <= pivote));
    do l--; while (Tvec[l] > pivote);
  }
  aux = Tvec[inicial];
  Tvec[inicial] = Tvec[l];
  Tvec[l] = aux;
  pp = l;
};

// ---- NUEVO: mergesort genérico ----
template <typename T>
inline static void mergesort(T Tvec[], int num_elem)
{
  mergesort_lims(Tvec, 0, num_elem);
}

template <typename T>
static void mergesort_lims(T Tvec[], int inicial, int final)
{
  if (final - inicial < UMBRAL) {
    insercion_lims(Tvec, inicial, final);
  } else {
    int k = inicial + (final - inicial) / 2;

    T *U = new T[k - inicial];
    assert(U);
    int l, l2;
    for (l = 0, l2 = inicial; l < k - inicial; l++, l2++)
      U[l] = Tvec[l2];

    T *V = new T[final - k];
    assert(V);
    for (l = 0, l2 = k; l < final - k; l++, l2++)
      V[l] = Tvec[l2];

    mergesort_lims(U, 0, k - inicial);
    mergesort_lims(V, 0, final - k);
    fusion(Tvec, inicial, final, U, V);

    delete [] U;
    delete [] V;
  }
}

template <typename T>
static void fusion(T Tvec[], int inicial, int final, T U[], T V[])
{
  int j = 0;
  int k = 0;
  int tamU = (final - inicial) / 2;
  int tamV = final - inicial - tamU;

  for (int i = inicial; i < final; i++) {
    if (j >= tamU) {
      Tvec[i] = V[k];
      k++;
    } else if (k >= tamV) {
      Tvec[i] = U[j];
      j++;
    } else if (U[j] < V[k]) {
      Tvec[i] = U[j];
      j++;
    } else {
      Tvec[i] = V[k];
      k++;
    }
  }
}

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

int EnteroAleatorio(const int cota_superior, const int cota_inferior) {
  return cota_inferior + rand() % (cota_superior - cota_inferior + 1);
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
    resultado += caracteres[rand() % 26];
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

template <typename T>
double medir_ordenacion(T* V, int n, const string& algoritmo) {
  double suma = 0.0;
  T* copia = new T[n];

  for (int i = 0; i < NUM_PRUEBAS; i++) {
    for (int j = 0; j < n; j++) {
      copia[j] = V[j];
    }

    auto start = chrono::high_resolution_clock::now();

    if (algoritmo == "quicksort") {
      quicksort(copia, n);
    } else if (algoritmo == "mergesort") {
      mergesort(copia, n);
    } else if (algoritmo == "insercion") {
      insercion(copia, n);
    }

    auto end = chrono::high_resolution_clock::now();
    suma += chrono::duration<double, std::milli>(end - start).count();
  }

  delete [] copia;
  return suma / NUM_PRUEBAS;
}

void Test(const int a, const int b, const int paso, const string algoritmo) {

  for (int i = a; i <= b; i+=paso) {
    //reservar 5 vectores:
    int *Enteros = new int[i];
    string *FijoPequeno = new string[i];
    string *FijoGrande = new string[i];
    string *Variable = new string[i];
    string *Prefijo = new string[i];

    //inicializar vectores
    srand(time(0));
    string prefijo = CalcularPrefijo(i);

    for (int j = 0; j < i; j++) {
      Enteros[j] = EnteroAleatorio(b, a);
      FijoPequeno[j] = StringFijo(5);
      FijoGrande[j] = StringFijo(500);
      Variable[j] = StringVariable(5,500);
      Prefijo[j] = StringPrefijo(prefijo, 15);
    }

    //ordenarlos y medir el tiempo

    double tiempo_enteros = medir_ordenacion(Enteros, i, algoritmo);
    double tiempo_fijo_pequeno = medir_ordenacion(FijoPequeno, i, algoritmo);
    double tiempo_fijo_grande = medir_ordenacion(FijoGrande, i, algoritmo);
    double tiempo_variable = medir_ordenacion(Variable, i, algoritmo);
    double tiempo_prefijo = medir_ordenacion(Prefijo, i, algoritmo);

    //imprimir resultados
    cout << i << "," << tiempo_enteros << "," << tiempo_fijo_pequeno << ","
         << tiempo_fijo_grande << "," << tiempo_variable << "," << tiempo_prefijo << endl;

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
    cin >> UMBRAL;
    cout << endl << "[a,b] =  ";
    int a, b, paso;
    cin >> a >> b;
    cout << endl << "Introduzca el paso: ";
    cin >> paso;
    assert(a<b && paso >= 1 && paso <= b-a);

    Test(a,b,paso, algoritmo);

  } else { //N fijo, Umbral Variable
      exit(-1);
  }

  return 0;
}
