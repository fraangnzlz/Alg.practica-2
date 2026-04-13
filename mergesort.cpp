#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>

inline static void mergesort(string T[], int num_elem);
static void mergesort_lims(string T[], int inicial, int final);
inline static void insercion(string T[], int num_elem);
static void insercion_lims(string T[], int inicial, int final);
static void fusion(string T[], int inicial, int final, string U[], string V[]);

inline static void mergesort_int(int T[], int num_elem);
static void mergesort_lims_int(int T[], int inicial, int final);
inline static void insercion_int(int T[], int num_elem);
static void insercion_lims_int(int T[], int inicial, int final);
static void fusion_int(int T[], int inicial, int final, int U[], int V[]);

int UMBRAL_MS = 256;

// STRING IMPLEMENTATIONS
inline static void insercion(string T[], int num_elem) { insercion_lims(T, 0, num_elem); }
static void insercion_lims(string T[], int inicial, int final) {
  int i, j; string aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((j>0) && (T[j]< T[j-1])) { aux = T[j]; T[j] = T[j-1]; T[j-1] = aux; j--; };
  };
}
void mergesort(string T[], int num_elem) { mergesort_lims(T, 0, num_elem); }
static void mergesort_lims(string T[], int inicial, int final) {
  if (final - inicial < UMBRAL_MS) { insercion_lims(T, inicial, final); } else {
      int k = (final - inicial)/2;
      string * U = new string [k - inicial + 1];
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++) U[l] = T[l2]; U[l] = "~";
      string * V = new string [final - k + 1];
      for (l = 0, l2 = k; l < final - k; l++, l2++) V[l] = T[l2]; V[l] = "~";
      mergesort_lims(U, 0, k); mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U; delete [] V;
    };
}
static void fusion(string T[], int inicial, int final, string U[], string V[]) {
  int j = 0; int k = 0;
  for (int i = inicial; i < final; i++) {
      if (U[j] < V[k]) { T[i] = U[j]; j++; } else { T[i] = V[k]; k++; };
  };
}

// INT IMPLEMENTATIONS
inline static void insercion_int(int T[], int num_elem) { insercion_lims_int(T, 0, num_elem); }
static void insercion_lims_int(int T[], int inicial, int final) {
  int i, j, aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((j>0) && (T[j]< T[j-1])) { aux = T[j]; T[j] = T[j-1]; T[j-1] = aux; j--; };
  };
}
void mergesort_int(int T[], int num_elem) { mergesort_lims_int(T, 0, num_elem); }
static void mergesort_lims_int(int T[], int inicial, int final) {
  if (final - inicial < UMBRAL_MS) { insercion_lims_int(T, inicial, final); } else {
      int k = (final - inicial)/2;
      int * U = new int [k - inicial + 1];
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++) U[l] = T[l2]; U[l] = 2147483647; // MAX_INT
      int * V = new int [final - k + 1];
      for (l = 0, l2 = k; l < final - k; l++, l2++) V[l] = T[l2]; V[l] = 2147483647; // MAX_INT
      mergesort_lims_int(U, 0, k); mergesort_lims_int(V, 0, final - k);
      fusion_int(T, inicial, final, U, V);
      delete [] U; delete [] V;
    };
}
static void fusion_int(int T[], int inicial, int final, int U[], int V[]) {
  int j = 0; int k = 0;
  for (int i = inicial; i < final; i++) {
      if (U[j] < V[k]) { T[i] = U[j]; j++; } else { T[i] = V[k]; k++; };
  };
}

// FUNCIONES PARA STRING FIJO, VARIABLE Y CON PREFIJO
string StringFijo(int longitud){
  string caracteres = "abcdefghijklmnopqrstuvwxyz"; string resultado; resultado.reserve(longitud);
  for(int i = 0; i < longitud; i++){ resultado += caracteres[rand() % 26]; }
  return resultado;
}
string StringVariable(int longitud_minima, int longitud_maxima){
  string caracteres = "abcdefghijklmnopqrstuvwxyz"; string resultado; resultado.reserve(longitud_maxima);
  int longitud = longitud_minima + rand() % (longitud_maxima - longitud_minima + 1);
  for(int i = 0; i < longitud; i++){ resultado += caracteres[rand() % 26]; }
  return resultado;
}
string StringPrefijo(string prefijo, int longitud_anadida){
  string caracteres = "abcdefghijklmnopqrstuvwxyz"; string resultado = prefijo;
  resultado.reserve(resultado.length() + longitud_anadida);
  for(int i = 0; i < longitud_anadida; i++) { resultado += caracteres[rand() % 26]; }
  return resultado;
}

int main(int argc, char * argv[]){
  if(argc != 5){
    cerr << "\nUso: " << argv[0] << " <tamanio> <umbral> <tipo_string (0=Int, 1=Fijo5, 2=Fijo500, 3=Var, 4=Prefijo)> <algoritmo (0=MergeSort, 1=Insercion)>" << endl;
    return -1;
  }
  int a = atoi(argv[1]);
  UMBRAL_MS = atoi(argv[2]);
  int tipo_string = atoi(argv[3]);
  int algoritmo = atoi(argv[4]);

  srand(time(0));
  auto start = chrono::high_resolution_clock::now();
  auto end = chrono::high_resolution_clock::now();

  if (tipo_string == 0) {
    int * V = new int[a];
    for(int i = 0; i < a; i++) V[i] = rand();
    start = chrono::high_resolution_clock::now();
    if (algoritmo == 1) insercion_int(V, a);
    else mergesort_int(V, a);
    end = chrono::high_resolution_clock::now();
    delete [] V;
  } else {
    string * V = new string[a];
    string prefijo_base = string(10, 'z');
    int long_extra = a * 0.01; if (long_extra < 1) long_extra = 1;
    for(int i = 0; i < a; i++) {
      switch (tipo_string) {
        case 1: V[i] = StringFijo(5); break;
        case 2: V[i] = StringFijo(500); break;
        case 3: V[i] = StringVariable(5,500); break;
        case 4: V[i] = StringPrefijo(prefijo_base, long_extra); break;
      }
    }
    start = chrono::high_resolution_clock::now();
    if (algoritmo == 1) insercion(V, a);
    else mergesort(V, a);
    end = chrono::high_resolution_clock::now();
    delete [] V;
  }

  chrono::duration<double,std::milli> duration = end - start;
  cout << "Algoritmo: " << algoritmo << " | Tamaño: " << a << " | Umbral: " << UMBRAL_MS << " | TipoString: " << tipo_string << " | Tiempo: " << duration.count() << endl;
  return 0;
}
