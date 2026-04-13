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
static void mergesort_lims(T Tvec[], int inicial, int final, T buffer[]);

template <typename T>
static void fusion(T Tvec[], int inicial, int medio, int final, T buffer[]);


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
    while ((Tvec[j] < Tvec[j-1]) && (j > inicial)) {
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
  T *buffer = new T[num_elem];
  mergesort_lims(Tvec, 0, num_elem, buffer);
  delete [] buffer;
}

template <typename T>
static void mergesort_lims(T Tvec[], int inicial, int final, T buffer[])
{
  if (final - inicial < UMBRAL) {
    insercion_lims(Tvec, inicial, final);
  } else {
    int medio = inicial + (final - inicial) / 2;

    mergesort_lims(Tvec, inicial, medio, buffer);
    mergesort_lims(Tvec, medio, final, buffer);
    fusion(Tvec, inicial, medio, final, buffer);
  }
}

template <typename T>
static void fusion(T Tvec[], int inicial, int medio, int final, T buffer[])
{
  int i = inicial;
  int j = medio;
  int k = 0;

  while (i < medio && j < final) {
    if (Tvec[i] < Tvec[j]) {
      buffer[k++] = Tvec[i++];
    } else {
      buffer[k++] = Tvec[j++];
    }
  }

  while (i < medio) {
    buffer[k++] = Tvec[i++];
  }

  while (j < final) {
    buffer[k++] = Tvec[j++];
  }

  for (int i = 0; i < k; i++) {
    Tvec[inicial + i] = buffer[i];
  }
}

string CalcularPrefijo(const int numDatos) {
  //El prefijo debe ser proporcional al numero de datos
  string prefijo = "prefijo";

  if (numDatos >= 100000) {
    int longitud = min(numDatos / 10000, 5);
    for (int i = 0; i < longitud; i++)
      prefijo += "_se_hace_mas_largo_y";
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

/**
 * @brief Función genérica para medir tiempos de un tipo de vector específico
 *
 * @tparam T Tipo de dato del vector
 * @tparam InitFunc Función de inicialización: void(T*, int, parametros_extra)
 * @param sizes Array con los tamaños/umbrales a probar
 * @param num_sizes Número de elementos en sizes
 * @param tiempos Array donde se guardarán los tiempos
 * @param algoritmo Nombre del algoritmo
 * @param init_func Función para inicializar el vector
 */
template <typename T, typename InitFunc>
void medir_tiempos_tipo(const int* sizes, int num_sizes, double* tiempos,
                        const string& algoritmo, InitFunc init_func) {
  for (int idx = 0; idx < num_sizes; idx++) {
    int n = sizes[idx];
    T* vec = new T[n];
    init_func(vec, n);
    tiempos[idx] = medir_ordenacion(vec, n, algoritmo);
    delete [] vec;
  }
}

/**
 * @brief Imprime los resultados en formato CSV
 */
void imprimir_resultados(const int* sizes, int num_sizes,
                        const double* tiempos_enteros,
                        const double* tiempos_fijo_pequeno,
                        const double* tiempos_fijo_grande,
                        const double* tiempos_variable,
                        const double* tiempos_prefijo) {
  for (int i = 0; i < num_sizes; i++) {
    cout << sizes[i] << "," << tiempos_enteros[i] << ","
         << tiempos_fijo_pequeno[i] << "," << tiempos_fijo_grande[i] << ","
         << tiempos_variable[i] << "," << tiempos_prefijo[i] << endl;
  }
}

// Funciones de inicialización para cada tipo
void init_enteros(int* vec, int n) {
  for (int i = 0; i < n; i++) {
    vec[i] = EnteroAleatorio(1000, 1);
  }
}

void init_fijo_pequeno(string* vec, int n) {
  for (int i = 0; i < n; i++) {
    vec[i] = StringFijo(5);
  }
}

void init_fijo_grande(string* vec, int n) {
  for (int i = 0; i < n; i++) {
    vec[i] = StringFijo(20);
  }
}

void init_variable(string* vec, int n) {
  for (int i = 0; i < n; i++) {
    vec[i] = StringVariable(5, 20);
  }
}

void init_prefijo(string* vec, int n) {
  string prefijo = CalcularPrefijo(n);
  for (int i = 0; i < n; i++) {
    vec[i] = StringPrefijo(prefijo, 10);
  }
}

void Test1(const int a, const int b, const int paso, const string algoritmo) {
  // Calcular número de tamaños a probar
  int num_tamaños = (b - a) / paso + 1;

  // Vectores para almacenar resultados de cada tamaño
  double *tiempos_enteros = new double[num_tamaños];
  double *tiempos_fijo_pequeno = new double[num_tamaños];
  double *tiempos_fijo_grande = new double[num_tamaños];
  double *tiempos_variable = new double[num_tamaños];
  double *tiempos_prefijo = new double[num_tamaños];
  int *tamaños_usados = new int[num_tamaños];

  // Procesar cada tipo de vector por separado
  // 1. Enteros
  int idx = 0;
  for (int i = a; i <= b; i += paso, idx++) {
    tamaños_usados[idx] = i;
    int *Enteros = new int[i];

    for (int j = 0; j < i; j++) {
      Enteros[j] = EnteroAleatorio(1000, 1);
    }
    tiempos_enteros[idx] = medir_ordenacion(Enteros, i, algoritmo);
    delete [] Enteros;
  }

  // 2. String Fijo Pequeño
  idx = 0;
  for (int i = a; i <= b; i += paso, idx++) {
    string *FijoPequeno = new string[i];
    for (int j = 0; j < i; j++) {
      FijoPequeno[j] = StringFijo(5);
    }
    tiempos_fijo_pequeno[idx] = medir_ordenacion(FijoPequeno, i, algoritmo);
    delete [] FijoPequeno;
  }

  // 3. String Fijo Grande
  idx = 0;
  for (int i = a; i <= b; i += paso, idx++) {
    string *FijoGrande = new string[i];
    for (int j = 0; j < i; j++) {
      FijoGrande[j] = StringFijo(20);
    }
    tiempos_fijo_grande[idx] = medir_ordenacion(FijoGrande, i, algoritmo);
    delete [] FijoGrande;
  }

  // 4. String Variable
  idx = 0;
  for (int i = a; i <= b; i += paso, idx++) {
    string *Variable = new string[i];
    for (int j = 0; j < i; j++) {
      Variable[j] = StringVariable(5, 20);
    }
    tiempos_variable[idx] = medir_ordenacion(Variable, i, algoritmo);
    delete [] Variable;
  }

  // 5. String con Prefijo
  idx = 0;
  for (int i = a; i <= b; i += paso, idx++) {
    string prefijo = CalcularPrefijo(i);
    string *Prefijo = new string[i];
    for (int j = 0; j < i; j++) {
      Prefijo[j] = StringPrefijo(prefijo, 10);
    }
    tiempos_prefijo[idx] = medir_ordenacion(Prefijo, i, algoritmo);
    delete [] Prefijo;
  }

  // Imprimir todos los resultados
  for (int i = 0; i < num_tamaños; i++) {
    cout << tamaños_usados[i] << "," << tiempos_enteros[i] << ","
         << tiempos_fijo_pequeno[i] << "," << tiempos_fijo_grande[i] << ","
         << tiempos_variable[i] << "," << tiempos_prefijo[i] << endl;
  }

  // Liberar arrays de resultados
  delete [] tiempos_enteros;
  delete [] tiempos_fijo_pequeno;
  delete [] tiempos_fijo_grande;
  delete [] tiempos_variable;
  delete [] tiempos_prefijo;
  delete [] tamaños_usados;
}

void Test2A(const int n, const int umbral_min, const int umbral_max, const string algoritmo) {
  // Iteracion lineal: umbral de 1 en 1
  // Calcular número de umbrales para reservar espacio
  int num_umbrales = umbral_max - umbral_min + 1;
  if (num_umbrales > 256) num_umbrales = 256 - umbral_min + 1;

  // Vectores para almacenar resultados de cada umbral
  double *tiempos_enteros = new double[num_umbrales];
  double *tiempos_fijo_pequeno = new double[num_umbrales];
  double *tiempos_fijo_grande = new double[num_umbrales];
  double *tiempos_variable = new double[num_umbrales];
  double *tiempos_prefijo = new double[num_umbrales];
  int *umbrales_usados = new int[num_umbrales];

  string prefijo = CalcularPrefijo(n);

  // Procesar cada tipo de vector por separado
  // 1. Enteros
  int *Enteros = new int[n];
  for (int j = 0; j < n; j++) {
    Enteros[j] = EnteroAleatorio(1000, 1);
  }
  int idx = 0;
  for (int umbral = umbral_min; umbral <= umbral_max && umbral <= 256; umbral++, idx++) {
    UMBRAL = umbral;
    umbrales_usados[idx] = umbral;
    tiempos_enteros[idx] = medir_ordenacion(Enteros, n, algoritmo);
  }
  delete [] Enteros;

  // 2. String Fijo Pequeño
  string *FijoPequeno = new string[n];
  for (int j = 0; j < n; j++) {
    FijoPequeno[j] = StringFijo(5);
  }
  idx = 0;
  for (int umbral = umbral_min; umbral <= umbral_max && umbral <= 256; umbral++, idx++) {
    UMBRAL = umbral;
    tiempos_fijo_pequeno[idx] = medir_ordenacion(FijoPequeno, n, algoritmo);
  }
  delete [] FijoPequeno;

  // 3. String Fijo Grande
  string *FijoGrande = new string[n];
  for (int j = 0; j < n; j++) {
    FijoGrande[j] = StringFijo(20);
  }
  idx = 0;
  for (int umbral = umbral_min; umbral <= umbral_max && umbral <= 256; umbral++, idx++) {
    UMBRAL = umbral;
    tiempos_fijo_grande[idx] = medir_ordenacion(FijoGrande, n, algoritmo);
  }
  delete [] FijoGrande;

  // 4. String Variable
  string *Variable = new string[n];
  for (int j = 0; j < n; j++) {
    Variable[j] = StringVariable(5, 20);
  }
  idx = 0;
  for (int umbral = umbral_min; umbral <= umbral_max && umbral <= 256; umbral++, idx++) {
    UMBRAL = umbral;
    tiempos_variable[idx] = medir_ordenacion(Variable, n, algoritmo);
  }
  delete [] Variable;

  // 5. String con Prefijo
  string *Prefijo = new string[n];
  for (int j = 0; j < n; j++) {
    Prefijo[j] = StringPrefijo(prefijo, 10);
  }
  idx = 0;
  for (int umbral = umbral_min; umbral <= umbral_max && umbral <= 256; umbral++, idx++) {
    UMBRAL = umbral;
    tiempos_prefijo[idx] = medir_ordenacion(Prefijo, n, algoritmo);
  }
  delete [] Prefijo;

  // Imprimir todos los resultados
  for (int i = 0; i < idx; i++) {
    cout << umbrales_usados[i] << "," << tiempos_enteros[i] << ","
         << tiempos_fijo_pequeno[i] << "," << tiempos_fijo_grande[i] << ","
         << tiempos_variable[i] << "," << tiempos_prefijo[i] << endl;
  }

  // Liberar arrays de resultados
  delete [] tiempos_enteros;
  delete [] tiempos_fijo_pequeno;
  delete [] tiempos_fijo_grande;
  delete [] tiempos_variable;
  delete [] tiempos_prefijo;
  delete [] umbrales_usados;
}

void Test2B(const int n, const int partida, const string algoritmo) {
  // Iteracion en potencias de 2
  // Calcular número de umbrales (máximo 8: 2, 4, 8, 16, 32, 64, 128, 256)
  int num_umbrales = 0;
  for (int u = partida; u <= 256; u *= 2) num_umbrales++;

  // Vectores para almacenar resultados de cada umbral
  double *tiempos_enteros = new double[num_umbrales];
  double *tiempos_fijo_pequeno = new double[num_umbrales];
  double *tiempos_fijo_grande = new double[num_umbrales];
  double *tiempos_variable = new double[num_umbrales];
  double *tiempos_prefijo = new double[num_umbrales];
  int *umbrales_usados = new int[num_umbrales];

  string prefijo = CalcularPrefijo(n);

  // Procesar cada tipo de vector por separado
  // 1. Enteros
  int *Enteros = new int[n];
  for (int j = 0; j < n; j++) {
    Enteros[j] = EnteroAleatorio(1000, 1);
  }
  int idx = 0;
  for (int umbral = partida; umbral <= 256; umbral *= 2, idx++) {
    UMBRAL = umbral;
    umbrales_usados[idx] = umbral;
    tiempos_enteros[idx] = medir_ordenacion(Enteros, n, algoritmo);
  }
  delete [] Enteros;

  // 2. String Fijo Pequeño
  string *FijoPequeno = new string[n];
  for (int j = 0; j < n; j++) {
    FijoPequeno[j] = StringFijo(5);
  }
  idx = 0;
  for (int umbral = partida; umbral <= 256; umbral *= 2, idx++) {
    UMBRAL = umbral;
    tiempos_fijo_pequeno[idx] = medir_ordenacion(FijoPequeno, n, algoritmo);
  }
  delete [] FijoPequeno;

  // 3. String Fijo Grande
  string *FijoGrande = new string[n];
  for (int j = 0; j < n; j++) {
    FijoGrande[j] = StringFijo(20);
  }
  idx = 0;
  for (int umbral = partida; umbral <= 256; umbral *= 2, idx++) {
    UMBRAL = umbral;
    tiempos_fijo_grande[idx] = medir_ordenacion(FijoGrande, n, algoritmo);
  }
  delete [] FijoGrande;

  // 4. String Variable
  string *Variable = new string[n];
  for (int j = 0; j < n; j++) {
    Variable[j] = StringVariable(5, 20);
  }
  idx = 0;
  for (int umbral = partida; umbral <= 256; umbral *= 2, idx++) {
    UMBRAL = umbral;
    tiempos_variable[idx] = medir_ordenacion(Variable, n, algoritmo);
  }
  delete [] Variable;

  // 5. String con Prefijo
  string *Prefijo = new string[n];
  for (int j = 0; j < n; j++) {
    Prefijo[j] = StringPrefijo(prefijo, 10);
  }
  idx = 0;
  for (int umbral = partida; umbral <= 256; umbral *= 2, idx++) {
    UMBRAL = umbral;
    tiempos_prefijo[idx] = medir_ordenacion(Prefijo, n, algoritmo);
  }
  delete [] Prefijo;

  // Imprimir todos los resultados
  for (int i = 0; i < num_umbrales; i++) {
    cout << umbrales_usados[i] << "," << tiempos_enteros[i] << ","
         << tiempos_fijo_pequeno[i] << "," << tiempos_fijo_grande[i] << ","
         << tiempos_variable[i] << "," << tiempos_prefijo[i] << endl;
  }

  // Liberar arrays de resultados
  delete [] tiempos_enteros;
  delete [] tiempos_fijo_pequeno;
  delete [] tiempos_fijo_grande;
  delete [] tiempos_variable;
  delete [] tiempos_prefijo;
  delete [] umbrales_usados;
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

  srand(time(0));
  if (opcion == 1) { //Umbral fijo, N variable
    cout << "Umbral: ";
    cin >> UMBRAL;
    cout << endl << "[a,b] =  ";
    int a, b, paso;
    cin >> a >> b;
    cout << endl << "Introduzca el paso: ";
    cin >> paso;
    assert(a<b && paso >= 1 && paso <= b-a);

    Test1(a,b,paso, algoritmo);

  } else { //N fijo, Umbral Variable
    int N;
    cout << "Numero de elementos (N): ";
    cin >> N;
    cout << endl << "Rango de umbrales [a,b]: ";
    int a, b, eleccion, partida=0;
    cin >> a >> b;
    cout << endl << "Modo de incremento:" << endl;
    cout << "  1) Paso lineal de 1 en 1" << endl;
    cout << "  2) Paso en potencias de 2 hasta 256" << endl;
    cout << "Opcion: ";
    cin >> eleccion;
    if (eleccion == 2) {
      cout << endl << "Introduzca el punto de partida (potencia de 2): ";
      cin >> partida;
      assert(partida >= 1 && partida <= 256);
    }
    assert(a < b && b <= 256 && (eleccion == 1 || eleccion == 2));

    if (eleccion == 1) {
      Test2A(N, a, b, algoritmo);
    } else {
      Test2B(N, partida, algoritmo);
    }
  }


  return 0;
}
