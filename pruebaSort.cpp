/**
   @file Ordenación rápida (quicksort).
*/

#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <string>
#include <chrono>
#include <fstream>

const double NUM_PRUEBAS = 10.f;

template <typename T>
static void quicksort_lims(T Tvec[], int inicial, int final);

template <typename T>
inline static void insercion(T Tvec[], int num_elem);

template <typename T>
static void insercion_lims(T Tvec[], int inicial, int final);

template <typename T>
static void dividir_qs(T Tvec[], int inicial, int final, int &pp);

template <typename T>
inline static void mergesort(T Tvec[], int num_elem);

template <typename T>
static void mergesort_lims(T Tvec[], int inicial, int final, T buffer[]);

template <typename T>
static void fusion(T Tvec[], int inicial, int medio, int final, T buffer[]);


/**
 * @brief Genera un prefijo cuya longitud crece con el número de datos.
 */
string CalcularPrefijo(const int numDatos);

/**
 * @brief Genera un entero aleatorio dentro de un rango cerrado.
 */
int EnteroAleatorio(const int cota_superior, const int cota_inferior);

/**
 * @brief Genera una cadena aleatoria de longitud fija.
 */
string StringFijo(const int longitud);

/**
 * @brief Genera una cadena aleatoria con longitud variable.
 */
string StringVariable(const int longitud_minima, const int longitud_maxima);

/**
 * @brief Genera una cadena aleatoria a partir de un prefijo dado.
 */
string StringPrefijo(const string prefijo, const int longitud_anadida);


// =========================================================
// Implementación de algoritmos de ordenación
// =========================================================

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
    while ((j > inicial) && (Tvec[j] < Tvec[j-1])) {
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
    if (Tvec[i] < Tvec[j])
      buffer[k++] = Tvec[i++];
    else
      buffer[k++] = Tvec[j++];
  }
  while (i < medio) buffer[k++] = Tvec[i++];
  while (j < final)  buffer[k++] = Tvec[j++];

  for (int i = 0; i < k; i++)
    Tvec[inicial + i] = buffer[i];
}


// =========================================================
// Generadores de datos
// =========================================================

string CalcularPrefijo(const int numDatos) {
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

string StringFijo(const int longitud) {
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado;
  resultado.reserve(longitud);
  for (int i = 0; i < longitud; i++)
    resultado += caracteres[rand() % caracteres.length()];
  return resultado;
}

string StringVariable(const int longitud_minima, const int longitud_maxima) {
  assert(longitud_maxima >= longitud_minima);
  string resultado;
  resultado.reserve(longitud_maxima);
  int longitud = longitud_minima + rand() % (longitud_maxima - longitud_minima + 1);
  for (int i = 0; i < longitud; i++)
    resultado += (char)('a' + rand() % 26);
  return resultado;
}

string StringPrefijo(const string prefijo, const int longitud_anadida) {
  string resultado = prefijo;
  resultado.reserve(resultado.length() + longitud_anadida);
  for (int i = 0; i < longitud_anadida; i++)
    resultado += (char)('a' + rand() % 26);
  return resultado;
}


// =========================================================
// Funciones de inicialización de vectores
// =========================================================

void init_enteros(int* vec, int n) {
  for (int i = 0; i < n; i++)
    vec[i] = EnteroAleatorio(INT_MAX, 1);
  //ponemos INT_MAX para que para numeros mas grandes no repita muchos numeros
  //y por ende no ocurra el problema del peor caso de quicksort
}

void init_fijo_pequeno(string* vec, int n) {
  for (int i = 0; i < n; i++)
    vec[i] = StringFijo(5);
}

void init_fijo_grande(string* vec, int n) {
  for (int i = 0; i < n; i++)
    vec[i] = StringFijo(20);
}

void init_variable(string* vec, int n) {
  for (int i = 0; i < n; i++)
    vec[i] = StringVariable(5, 20);
}

void init_prefijo(string* vec, int n) {
  string prefijo = CalcularPrefijo(n);
  for (int i = 0; i < n; i++)
    vec[i] = StringPrefijo(prefijo, 10);
}


// =========================================================
// Medición de tiempos
// =========================================================

/**
 * @brief Ordena una copia del vector NUM_PRUEBAS veces y devuelve el tiempo medio (ms).
 *
 * @tparam T Tipo de los elementos.
 * @param V Vector original (no se modifica).
 * @param n Número de elementos.
 * @param algoritmo "quicksort", "mergesort" o "insercion".
 * @return Tiempo medio en milisegundos.
 */
template <typename T>
double medir_ordenacion(T* V, int n, const string& algoritmo) {
  double suma = 0.0;
  T* copia = new T[n];

  for (int i = 0; i < NUM_PRUEBAS; i++) {
    for (int j = 0; j < n; j++) copia[j] = V[j];

    auto start = chrono::high_resolution_clock::now();

    if      (algoritmo == "quicksort")  quicksort(copia, n);
    else if (algoritmo == "mergesort")  mergesort(copia, n);
    else if (algoritmo == "insercion")  insercion(copia, n);

    auto end = chrono::high_resolution_clock::now();
    suma += chrono::duration<double, milli>(end - start).count();

    //como lo compilamos con la optimizacion -O3, asi evitamos
    //que se carge a la copia porque no la usamos tras ordenarla
    volatile T dummy = copia[n / 2];
    (void)dummy;

   }

  delete [] copia;
  return suma / NUM_PRUEBAS;
}

/**
 * @brief Mide tiempos de ordenación para distintos tamaños de vector (UMBRAL fijo).
 *
 * Para cada tamaño en @p sizes crea un vector con @p init_func,
 * llama a medir_ordenacion y almacena el resultado en @p tiempos.
 *
 * @tparam T        Tipo de los elementos del vector.
 * @tparam InitFunc Callable con firma void(T*, int).
 * @param sizes     Array de tamaños a probar.
 * @param num_sizes Número de elementos en @p sizes.
 * @param tiempos   Array de salida con los tiempos medidos.
 * @param algoritmo Nombre del algoritmo.
 * @param init_func Función de inicialización del vector.
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
 * @brief Mide tiempos de ordenación para distintos umbrales (N fijo).
 *
 * Itera sobre @p umbrales, ajusta la variable global UMBRAL y mide el
 * tiempo sobre el vector @p vec ya inicializado.
 *
 * @tparam T           Tipo de los elementos del vector.
 * @param vec          Vector ya inicializado de tamaño @p n.
 * @param n            Número de elementos.
 * @param umbrales     Array de valores de umbral a probar.
 * @param num_umbrales Número de elementos en @p umbrales.
 * @param tiempos      Array de salida con los tiempos medidos.
 * @param algoritmo    Nombre del algoritmo.
 */
template <typename T>
void medir_tiempos_umbral(T* vec, int n, const int* umbrales, int num_umbrales,
                           double* tiempos, const string& algoritmo) {
  for (int idx = 0; idx < num_umbrales; idx++) {
    UMBRAL = umbrales[idx];
    tiempos[idx] = medir_ordenacion(vec, n, algoritmo);
  }
}

template <typename T>
void medir_tipo(int n, const int* umbrales, int num_umbrales, const string& algoritmo, double* tiempos_dst, void (*init_fn)(T*, int)) {

  T* v = new T[n];
  init_fn(v, n);
  medir_tiempos_umbral(v, n, umbrales, num_umbrales, tiempos_dst, algoritmo);
  delete[] v;
}

/**
 * @brief Imprime los resultados en un .txt
 *
 * Primera columna: parámetro variable (N o umbral).
 * Columnas 2-6:   tiempos para cada tipo de dato.
 */

void imprimir_resultados(const string& nombre_archivo,
                         const int* param, int num,
                         const double* tiempos_enteros,
                         const double* tiempos_fijo_pequeno,
                         const double* tiempos_fijo_grande,
                         const double* tiempos_variable,
                         const double* tiempos_prefijo) {

  ofstream archivo(nombre_archivo);

  if (!archivo.is_open()) {
    cerr << "Error: No se pudo abrir o crear el archivo " << nombre_archivo << "\n";
    return;
  }
    archivo << "Umbral\t Enteros\t StringFP\t StringFG\t StringVar\t StringP \n";
  for (int i = 0; i < num; i++) {
    archivo << param[i]              << "\t"
            << tiempos_enteros[i]    << "\t"
            << tiempos_fijo_pequeno[i] << "\t"
            << tiempos_fijo_grande[i]  << "\t"
            << tiempos_variable[i]     << "\t"
            << tiempos_prefijo[i]      << "\n";
  }

  archivo.close();
}


// =========================================================
// Funciones de experimento
// =========================================================

/**
 * @brief Experimento con UMBRAL fijo y número de elementos variable.
 *
 * Para cada tamaño en [a, b] con paso @p paso mide el tiempo de @p algoritmo
 * sobre cinco tipos de datos y lo imprime en CSV.
 */
void Test1(const int a, const int b, const int paso, const string algoritmo) {
  // Construir array de tamaños
  int num_tamanios = (b - a) / paso + 1;
  int* tamanios = new int[num_tamanios];
  for (int i = 0; i < num_tamanios; i++)
    tamanios[i] = a + i * paso;

  // Reservar arrays de tiempos
  double* tiempos_enteros      = new double[num_tamanios];
  double* tiempos_fijo_pequeno = new double[num_tamanios];
  double* tiempos_fijo_grande  = new double[num_tamanios];
  double* tiempos_variable     = new double[num_tamanios];
  double* tiempos_prefijo      = new double[num_tamanios];

  // Medir cada tipo de dato usando el helper genérico
  medir_tiempos_tipo<int>   (tamanios, num_tamanios, tiempos_enteros,      algoritmo, init_enteros);
  medir_tiempos_tipo<string>(tamanios, num_tamanios, tiempos_fijo_pequeno, algoritmo, init_fijo_pequeno);
  medir_tiempos_tipo<string>(tamanios, num_tamanios, tiempos_fijo_grande,  algoritmo, init_fijo_grande);
  medir_tiempos_tipo<string>(tamanios, num_tamanios, tiempos_variable,     algoritmo, init_variable);
  medir_tiempos_tipo<string>(tamanios, num_tamanios, tiempos_prefijo,      algoritmo, init_prefijo);

  imprimir_resultados("resultados.txt",tamanios, num_tamanios,
                      tiempos_enteros, tiempos_fijo_pequeno, tiempos_fijo_grande,
                      tiempos_variable, tiempos_prefijo);

  delete[] tamanios;
  delete[] tiempos_enteros; delete[] tiempos_fijo_pequeno; delete[] tiempos_fijo_grande;
  delete[] tiempos_variable; delete[] tiempos_prefijo;
}

/**
 * @brief Núcleo compartido de Test2A y Test2B.
 *
 * Dado un array de umbrales ya construido, crea un vector por cada tipo de dato,
 * mide los tiempos barriendo todos los umbrales y los imprime en CSV.
 *
 * @param n            Número de elementos del vector (fijo).
 * @param umbrales     Array de valores de umbral a probar.
 * @param num_umbrales Número de elementos en @p umbrales.
 * @param algoritmo    Nombre del algoritmo.
 */
void Test2_impl(const int n, const int* umbrales, int num_umbrales,
                const string& algoritmo) {
  double* tiempos_enteros      = new double[num_umbrales];
  double* tiempos_fijo_pequeno = new double[num_umbrales];
  double* tiempos_fijo_grande  = new double[num_umbrales];
  double* tiempos_variable     = new double[num_umbrales];
  double* tiempos_prefijo      = new double[num_umbrales];

  medir_tipo<int>   (n, umbrales, num_umbrales, algoritmo, tiempos_enteros,      init_enteros);
  medir_tipo<string>(n, umbrales, num_umbrales, algoritmo, tiempos_fijo_pequeno, init_fijo_pequeno);
  medir_tipo<string>(n, umbrales, num_umbrales, algoritmo, tiempos_fijo_grande,  init_fijo_grande);
  medir_tipo<string>(n, umbrales, num_umbrales, algoritmo, tiempos_variable,     init_variable);
  medir_tipo<string>(n, umbrales, num_umbrales, algoritmo, tiempos_prefijo,      init_prefijo);

  imprimir_resultados("resultados.txt",umbrales, num_umbrales, tiempos_enteros, tiempos_fijo_pequeno, tiempos_fijo_grande,
                      tiempos_variable, tiempos_prefijo);

  delete[] tiempos_enteros; delete[] tiempos_fijo_pequeno; delete[] tiempos_fijo_grande;
  delete[] tiempos_variable; delete[] tiempos_prefijo;
}

/**
 * @brief Experimento con N fijo y umbral variable (paso lineal de 1 en 1).
 *
 * Prueba todos los umbrales en [umbral_min, min(umbral_max, 256)].
 */
void Test2A(const int n, const int umbral_min, const int umbral_max, const int paso, const string algoritmo) {

  int limite       = min(umbral_max, 256);
  int num_umbrales = (limite - umbral_min) / paso + 1;

  int* umbrales = new int[num_umbrales];
  for (int i = 0; i < num_umbrales; i++)
    umbrales[i] = umbral_min + i * paso;

  Test2_impl(n, umbrales, num_umbrales, algoritmo);

  delete[] umbrales;
}

/**
 * @brief Experimento con N fijo y umbral variable (potencias de 2 hasta 256).
 *
 * Prueba los umbrales partida, partida*2, partida*4, …, hasta 256.
 */
void Test2B(const int n, const int partida, const string algoritmo) {
  // Contar cuántos umbrales habrá
  int num_umbrales = 0;
  for (int u = partida; u <= 256; u *= 2) num_umbrales++;

  int* umbrales = new int[num_umbrales];
  int idx = 0;
  for (int u = partida; u <= 256; u *= 2)
    umbrales[idx++] = u;

  Test2_impl(n, umbrales, num_umbrales, algoritmo);

  delete[] umbrales;
}


// =========================================================
// main
// =========================================================

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
  cout << "\nElige el tipo de experimento:\n"
       << "  1) Umbral fijo con numero de elementos variable\n"
       << "  2) Umbral variable con numero de elementos fijo\n"
       << "Opcion: ";
  cin >> opcion;

  if (opcion != 1 && opcion != 2) {
    cerr << "Error: opcion no valida." << endl;
    return -1;
  }

  srand(time(0));

  if (opcion == 1) {
    cout << "Umbral: ";
    cin >> UMBRAL;
    cout << "\n[a,b] = ";
    int a, b, paso;
    cin >> a >> b;
    cout << "\nIntroduzca el paso: ";
    cin >> paso;
    assert(a < b && paso >= 1 && paso <= b - a);

    Test1(a, b, paso, algoritmo);

  } else {
    int N;
    cout << "Numero de elementos (N): ";
    cin >> N;
    cout << "\nRango de umbrales [a,b]: ";
    int a, b, eleccion, partida = 0;
    cin >> a >> b;
    cout << "\nModo de incremento:\n"
         << "  1) Paso lineal\n"
         << "  2) Paso en potencias de 2 hasta 256\n"
         << "Opcion: ";
    cin >> eleccion;
    if (eleccion == 2) {
      cout << "\nIntroduzca el punto de partida (potencia de 2): ";
      cin >> partida;
      assert(partida >= 1 && partida <= 256);
    }
    assert(a < b && b <= 256 && (eleccion == 1 || eleccion == 2));

    if (eleccion == 1) {
      int paso;
      cout << "\nIntroduzca el paso: ";
      cin >> paso;
      assert(paso >= 1 && paso <= b - a);
      Test2A(N, a, b, paso, algoritmo);
    } else {
      Test2B(N, partida, algoritmo);
    }
  }

  return 0;
}